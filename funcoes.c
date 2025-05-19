/** ***************************************************************
 * @file   funcoes.c
 * @brief  Implementação das funções principais do projeto
 * @author Nelson Cruz, aluno 31103
 * @date   Maio 2025
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
#include <locale.h>

Antena* criarAntena(char frequencia, int x, int y) {
    Antena* nova = (Antena*)malloc(sizeof(Antena));
    if (!nova) return NULL;
    nova->frequencia = frequencia;
    nova->x = x;
    nova->y = y;
    nova->prox = NULL;
    nova->adj = NULL; // Inicializa sem adjacências
    return nova;
}

Antena* inserirAntena(Antena* a, Antena* inicio, Grafo* g) {
    // Verifica se o apontador para a nova antena é nulo
    if (!a) return inicio;

    // Se o grafo for fornecido, incrementa o número total de antenas
    if (g) {
        g->totalAntenas++;
        printf("Inserida antena %c (%d,%d)\n", a->frequencia, a->x, a->y);  // Mensagem de debug
    }

    // Caso especial: inserir no início da lista (lista vazia ou nova antena vem antes da primeira)
    if (!inicio || (a->x < inicio->x) || (a->x == inicio->x && a->y < inicio->y)) {
        a->prox = inicio;
		return a; // A nova antena torna-se o novo início da lista
    }

    // Percorre a lista para encontrar a posição correta de inserção
    Antena* aux1 = inicio;
    Antena* aux2 = inicio->prox;

    // Avança enquanto a nova antena for "maior" que a atual (em x ou, em caso de empate, em y)
    while (aux2 && (a->x > aux2->x || (a->x == aux2->x && a->y > aux2->y))) {
        aux1 = aux2;
        aux2 = aux2->prox;
    }

    // Insere a nova antena entre aux1 e aux2
    a->prox = aux2;
    aux1->prox = a;

    // A cabeça da lista mantém-se
    return inicio;
}



Antena* carregarFicheiro(const char* nomeFicheiro) {
    // Abre o ficheiro de texto para leitura
    FILE* f = fopen(nomeFicheiro, "r");
    if (!f) return NULL; // Se não conseguir abrir o ficheiro, retorna NULL

    Antena* lista = NULL;     // Ponteiro para o início da lista ligada de antenas
    char linha[100];          // Buffer para armazenar cada linha do ficheiro
    int y = 0;                // Coordenada vertical (linha da matriz)

    // Lê o ficheiro linha a linha
    while (fgets(linha, sizeof(linha), f)) {
        // Percorre cada caractere da linha
        for (int x = 0; linha[x] != '\0' && linha[x] != '\n'; x++) {
            char c = linha[x];

            // Ignora pontos, espaços e quebras de linha
            if (c != '.' && c != ' ' && c != '\n') {
                // Cria uma nova antena com o caractere e coordenadas (x, y)
                Antena* nova = criarAntena(c, x, y);

                // Insere a antena na lista ligada de forma ordenada
                lista = inserirAntena(nova, lista, NULL);
            }
        }
        y++; // Incrementa a coordenada vertical
    }

    fclose(f); // Fecha o ficheiro após a leitura
    return lista; // Retorna a lista de antenas carregadas
}


void listarAntenas(Antena* inicio) { //não estou a usar
    Antena* atual = inicio;
    while (atual) {
        // Aqui apenas se percorre a lista. Não se imprime nada.
        // funcao de teste para ver se esta a percorrer a lista
        //printf("%c (%d,%d)\n", atual->frequencia, atual->x, atual->y);
        atual = atual->prox;
    }
}

void listarAdjacencias(Antena* inicio) {
    Antena* atual = inicio;

    // Percorre toda a lista de antenas
    while (atual) {
        // Imprime a antena atual
        printf("Antena %c (%d,%d) está ligada a:\n", atual->frequencia, atual->x, atual->y);

        // Percorre a lista de adjacências desta antena
        Adjacencia* adj = atual->adj;
        while (adj) {
            // Imprime a antena de destino da ligação
            printf("  -> %c (%d,%d)\n", adj->destino->frequencia, adj->destino->x, adj->destino->y);
            adj = adj->prox; // Passa à próxima adjacência
        }

        // Avança para a próxima antena na lista
        atual = atual->prox;
    }
}


Grafo* criarGrafo() {
    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    if (!g) return NULL;
    g->vertices = NULL;
    g->totalAntenas = 0;
    return g;
}

void libertarGrafo(Grafo* g) {
    if (!g) return;

    Antena* v = g->vertices;
    while (v) {
        Adjacencia* adj = v->adj;
        while (adj) {
            Adjacencia* tempAdj = adj;
            adj = adj->prox;
            free(tempAdj);
        }
        Antena* tempV = v;
        v = v->prox;
        free(tempV);
    }
    free(g);
}

void ligarAntenas(Antena* a, Antena* b) {
    // Verifica se os apontadores são válidos
    if (!a || !b) return;

    // Só liga antenas com a mesma frequência
    if (a->frequencia != b->frequencia) return;

    // Cria a adjacência de 'a' para 'b'
    Adjacencia* novaAdj = (Adjacencia*)malloc(sizeof(Adjacencia));
    if (!novaAdj) return; // Falha na alocação de memória
    novaAdj->destino = b;      // Define a antena de destino
    novaAdj->prox = a->adj;    // Liga ao início da lista de adjacências de 'a'
    a->adj = novaAdj;          // Atualiza a cabeça da lista de adjacências de 'a'

    // Cria a adjacência de 'b' para 'a' (ligação bidirecional)
    Adjacencia* novaAdj2 = (Adjacencia*)malloc(sizeof(Adjacencia));
    if (!novaAdj2) return; // Falha na alocação de memória
    novaAdj2->destino = a;
    novaAdj2->prox = b->adj;
    b->adj = novaAdj2;
}


#pragma region Binario

void guardarGrafoBinario(const char* nomeFicheiro, Grafo* g) {
    if (!g || !nomeFicheiro) return;

    FILE* f = fopen(nomeFicheiro, "wb");
    if (!f) {
        perror("Erro ao abrir ficheiro binário para escrita");
        return;
    }

    // Escrever o total de antenas
    fwrite(&g->totalAntenas, sizeof(int), 1, f);

    // Percorrer todas as antenas
    Antena* atual = g->vertices;
    while (atual) {
        // Converter para estrutura binária
        AntenaBin ab;
        ab.frequencia = atual->frequencia;
        ab.x = atual->x;
        ab.y = atual->y;

        fwrite(&ab, sizeof(AntenaBin), 1, f);

        // Contar adjacências
        int totalAdj = 0;
        Adjacencia* a = atual->adj;
        while (a) {
            totalAdj++;
            a = a->prox;
        }

        fwrite(&totalAdj, sizeof(int), 1, f);

        // Escrever todas as adjacências
        a = atual->adj;
        while (a) {
            AdjacenciaBin adjBin;
            adjBin.x = a->destino->x;
            adjBin.y = a->destino->y;
            fwrite(&adjBin, sizeof(AdjacenciaBin), 1, f);
            a = a->prox;
        }

        atual = atual->prox;
    }

    fclose(f);
}

Grafo* lerGrafoBinario(const char* nomeFicheiro) {
    // Abre o ficheiro binário para leitura
    FILE* f = fopen(nomeFicheiro, "rb");
    if (!f) {
        perror("Erro ao abrir ficheiro binário para leitura");
        return NULL;
    }

    // Cria e inicializa o grafo
    Grafo* g = criarGrafo();
    if (!g) return NULL;

    int total;
    // Lê o número total de antenas guardado no início do ficheiro
    fread(&total, sizeof(int), 1, f);
    g->totalAntenas = total;

    // Para cada antena gravada no ficheiro
    for (int i = 0; i < total; i++) {
        AntenaBin ab;

        // Lê os dados da antena (sem apontadores)
        fread(&ab, sizeof(AntenaBin), 1, f);

        // Cria a antena e insere no grafo (lista ligada de vértices)
        Antena* nova = criarAntena(ab.frequencia, ab.x, ab.y);
        g->vertices = inserirAntena(nova, g->vertices, g);

        int totalAdj;
        // Lê o número de adjacências desta antena
        fread(&totalAdj, sizeof(int), 1, f);

        // Para cada adjacência lida
        for (int j = 0; j < totalAdj; j++) {
            AdjacenciaBin ajb;
            fread(&ajb, sizeof(AdjacenciaBin), 1, f);

            // Procura a antena de destino com coordenadas correspondentes
            Antena* destino = g->vertices;
            while (destino && (destino->x != ajb.x || destino->y != ajb.y)) {
                destino = destino->prox;
            }

            // Se encontrada, cria a adjacência na antena atual
            if (destino) {
                Adjacencia* novaAdj = (Adjacencia*)malloc(sizeof(Adjacencia));
                novaAdj->destino = destino;
                novaAdj->prox = nova->adj;
                nova->adj = novaAdj;
            }
        }
    }

    fclose(f); // Fecha o ficheiro após leitura
    return g;  // Devolve o grafo carregado
}

void listarConteudoBinario(const char* nomeFicheiro) {
    // Abre o ficheiro binário para leitura
    FILE* f = fopen(nomeFicheiro, "rb");
    if (!f) {
        perror("Erro ao abrir ficheiro binário");
        return;
    }

    int total;
    // Lê o número total de antenas guardado no início do ficheiro
    fread(&total, sizeof(int), 1, f);
    printf("Total de antenas no ficheiro binário: %d\n", total); // Validação para testes

    // Percorre cada antena gravada
    for (int i = 0; i < total; i++) {
        AntenaBin ab;
        fread(&ab, sizeof(AntenaBin), 1, f); // Lê os dados da antena
        printf("- Antena %c (%d,%d):\n", ab.frequencia, ab.x, ab.y); // Mostra a antena

        int totalAdj;
        fread(&totalAdj, sizeof(int), 1, f); // Lê o número de adjacências desta antena

        // Mostra cada coordenada de antena ligada (adjacente)
        for (int j = 0; j < totalAdj; j++) {
            AdjacenciaBin ajb;
            fread(&ajb, sizeof(AdjacenciaBin), 1, f);
            printf("   -> ligada a (%d,%d)\n", ajb.x, ajb.y); // Validação simples
        }
    }

    fclose(f); // Fecha o ficheiro após leitura
}



#pragma endregion

