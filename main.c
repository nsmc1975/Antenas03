/** ***************************************************************
 * @file   main.c
 * @brief  Programa principal de testes do projeto de EDA
 * @author Nelson Cruz, aluno 31103
 * @date   Maio 2025
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese");
    // Criar o grafo vazio
    
    Grafo* g = criarGrafo();
    g->vertices = NULL;
    g->totalAntenas = 0;

    // Carregar antenas de ficheiro e inserir diretamente no grafo
    Antena* carregadas = carregarFicheiro("antenas.txt");
    Antena* temp = carregadas;
    while (temp) {
        Antena* nova = criarAntena(temp->frequencia, temp->x, temp->y);
        nova->prox = NULL; // evitar que a antena traga a lista original ligada
        g->vertices = inserirAntena(nova, g->vertices, g);
        temp = temp->prox;
    }

    // Criar manualmente 3 antenas com a mesma frequência
    Antena* a1 = criarAntena('B', 2, 3);
    Antena* a2 = criarAntena('B', 5, 3);
    Antena* a3 = criarAntena('B', 8, 3);

    // Inserir as antenas no grafo
    g->vertices = inserirAntena(a1, g->vertices, g);
    g->vertices = inserirAntena(a2, g->vertices, g);
    g->vertices = inserirAntena(a3, g->vertices, g);

    // Ligar antenas entre si
    ligarAntenas(a1, a2);
    ligarAntenas(a2, a3);

    // Mostrar antenas e suas adjacências
    Antena* atual = g->vertices;
    printf("Antenas no grafo (total = %d):\n", g->totalAntenas);
    while (atual) {
        printf("- Antena %c (%d,%d):\n", atual->frequencia, atual->x, atual->y);
        Adjacencia* adj = atual->adj;
        while (adj) {
            printf("   -> ligada a %c (%d,%d)\n", adj->destino->frequencia, adj->destino->x, adj->destino->y);
            adj = adj->prox;
        }
        atual = atual->prox;
    }



	guardarGrafoBinario("grafo.bin", g);
    listarConteudoBinario("grafo.bin");


    printf("chegou ao fim, vai libertar memoria");

        // Libertar lista carregada original
        while (carregadas) {
            Antena* apagar = carregadas;
            carregadas = carregadas->prox;
            free(apagar);
        }
        printf("\nTotal final de antenas no grafo: %d\n", g->totalAntenas);
        libertarGrafo(g);
    

    return 0;
}
