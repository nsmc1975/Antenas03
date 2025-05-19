/** ***************************************************************
 * @file   funcoes.h
 * @brief  Declara��o das fun��es principais do projeto
 * @author Nelson Cruz, aluno 31103
 * @date   Maio 2025
 ****************************************************************/

#ifndef FUNCOES_H
#define FUNCOES_H

#include "dados.h"

 /**
  * @brief Cria uma nova antena com os dados fornecidos
  * @param frequencia Car�cter da frequ�ncia
  * @param x Coordenada x da antena
  * @param y Coordenada y da antena
  * @return Apontador para a antena criada
  */
Antena* criarAntena(char frequencia, int x, int y);

/**
 * @brief Insere uma antena na lista ligada, por ordem de coordenadas
 * @param a Apontador para a antena a inserir
 * @param inicio Apontador para o in�cio da lista
 * @return Novo in�cio da lista ligada
 */
Antena* inserirAntena(Antena* a, Antena* inicio, Grafo* g);

/**
 * @brief Carrega antenas de um ficheiro de texto com mapa de frequ�ncias
 * @param nomeFicheiro Nome do ficheiro a ler
 * @return Lista ligada de antenas carregadas
 */
Antena* carregarFicheiro(const char* nomeFicheiro);

/**
 * @brief Percorre a lista de antenas (sem imprimir)
 * @param inicio Apontador para o in�cio da lista de antenas
 */
void listarAntenas(Antena* inicio);

/**
 * @brief Cria e inicializa um grafo vazio
 * @return Apontador para o grafo criado
 */
Grafo* criarGrafo();

/**
 * @brief Liberta toda a mem�ria ocupada pelo grafo e suas listas
 * @param g Apontador para o grafo
 */
void libertarGrafo(Grafo* g);

/**
 * @brief Liga duas antenas entre si, se tiverem a mesma frequ�ncia
 *        (liga��o bidirecional)
 * @param a Apontador para a antena de origem
 * @param b Apontador para a antena de destino
 */
void ligarAntenas(Antena* a, Antena* b);

/**
 * @brief Fun��o de teste para mostrar as adjac�ncias de cada antena
 * @param inicio Apontador para a lista ligada de antenas
 */
void listarAdjacencias(Antena* inicio);


/**
 * @brief Fun��o para guardar o grafo em ficheiro binario
 * @param guarda cada antena seguida das suas adjacencias todas e so depois a proxima antena
 */
void guardarGrafoBinario(const char* nomeFicheiro, Grafo* g);

/**
 * @brief Fun��o para ler de um binario e gravar na struct grafo
 * @param le uma antena e a suas adjacencias a seguir
 */
Grafo* lerGrafoBinario(const char* nomeFicheiro);

/**
 * @brief Fun��o para listar o conte�do de um ficheiro bin�rio
 * @param nomeFicheiro Nome do ficheiro a ler
 */
void listarConteudoBinario(const char* nomeFicheiro);

#endif // FUNCOES_H