/** ***************************************************************
 * @file   funcoes.h
 * @brief  Declaração das funções principais do projeto
 * @author Nelson Cruz, aluno 31103
 * @date   Maio 2025
 ****************************************************************/

#ifndef FUNCOES_H
#define FUNCOES_H

#include "dados.h"

 /**
  * @brief Cria uma nova antena com os dados fornecidos
  * @param frequencia Carácter da frequência
  * @param x Coordenada x da antena
  * @param y Coordenada y da antena
  * @return Apontador para a antena criada
  */
Antena* criarAntena(char frequencia, int x, int y);

/**
 * @brief Insere uma antena na lista ligada, por ordem de coordenadas
 * @param a Apontador para a antena a inserir
 * @param inicio Apontador para o início da lista
 * @return Novo início da lista ligada
 */
Antena* inserirAntena(Antena* a, Antena* inicio, Grafo* g);

/**
 * @brief Carrega antenas de um ficheiro de texto com mapa de frequências
 * @param nomeFicheiro Nome do ficheiro a ler
 * @return Lista ligada de antenas carregadas
 */
Antena* carregarFicheiro(const char* nomeFicheiro);

/**
 * @brief Percorre a lista de antenas (sem imprimir)
 * @param inicio Apontador para o início da lista de antenas
 */
void listarAntenas(Antena* inicio);

/**
 * @brief Cria e inicializa um grafo vazio
 * @return Apontador para o grafo criado
 */
Grafo* criarGrafo();

/**
 * @brief Liberta toda a memória ocupada pelo grafo e suas listas
 * @param g Apontador para o grafo
 */
void libertarGrafo(Grafo* g);

/**
 * @brief Liga duas antenas entre si, se tiverem a mesma frequência
 *        (ligação bidirecional)
 * @param a Apontador para a antena de origem
 * @param b Apontador para a antena de destino
 */
void ligarAntenas(Antena* a, Antena* b);

/**
 * @brief Função de teste para mostrar as adjacências de cada antena
 * @param inicio Apontador para a lista ligada de antenas
 */
void listarAdjacencias(Antena* inicio);


/**
 * @brief Função para guardar o grafo em ficheiro binario
 * @param guarda cada antena seguida das suas adjacencias todas e so depois a proxima antena
 */
void guardarGrafoBinario(const char* nomeFicheiro, Grafo* g);

/**
 * @brief Função para ler de um binario e gravar na struct grafo
 * @param le uma antena e a suas adjacencias a seguir
 */
Grafo* lerGrafoBinario(const char* nomeFicheiro);

/**
 * @brief Função para listar o conteúdo de um ficheiro binário
 * @param nomeFicheiro Nome do ficheiro a ler
 */
void listarConteudoBinario(const char* nomeFicheiro);

#endif // FUNCOES_H