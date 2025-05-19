/** ***************************************************************
 * @file   dados.h
 * @brief  Definição das estruturas de dados principais do projeto
 * @author Nelson Cruz, aluno 31103
 * @date   Maio 2025
 ****************************************************************/

#ifndef DADOS_H
#define DADOS_H
typedef struct Antena;

typedef struct Adjacencia {
    struct Antena* destino;
    struct Adjacencia* prox;
} Adjacencia;

typedef struct Antena {
    char frequencia;
    int x, y;
    struct Antena* prox;
    Adjacencia* adj;
} Antena;

typedef struct Grafo {
    Antena* vertices;
    int totalAntenas;
} Grafo;

/**
 * @struct AntenaBin
 * @brief Estrutura simplificada para escrita binária (sem apontadores)
 */
typedef struct AntenaBin{
    char frequencia;
    int x, y;
} AntenaBin;

/**
 * @struct AdjacenciaBin
 * @brief Representa uma adjacência em ficheiro binário (apenas coordenadas)
 */
typedef struct AdjacenciaBin {
    int x, y;  /**< Coordenadas da antena de destino */
} AdjacenciaBin;

#endif // DADOS_H
