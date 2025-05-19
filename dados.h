/** ***************************************************************
 * @file   dados.h
 * @brief  Defini��o das estruturas de dados principais do projeto
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
 * @brief Estrutura simplificada para escrita bin�ria (sem apontadores)
 */
typedef struct AntenaBin{
    char frequencia;
    int x, y;
} AntenaBin;

/**
 * @struct AdjacenciaBin
 * @brief Representa uma adjac�ncia em ficheiro bin�rio (apenas coordenadas)
 */
typedef struct AdjacenciaBin {
    int x, y;  /**< Coordenadas da antena de destino */
} AdjacenciaBin;

#endif // DADOS_H
