//
// Created by limahrc on 09/06/18.
// github.com/limahrc/sieve
//



#ifndef _SIEVE_H_
#define _SIEVE_H_

// bibliotecas necessárias para o correto funcionamento do programa
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include "ints.h"

/**
 * Buffer interno das sieves.
 *
 * TAD contendo campos vitais para o funcionamento, acesso
 * e cálculos realizados pelas threads de sieve.
 *
 * @field id: identificação numérica da sieve
 * @field reg: lista encadeada de números primos registrados
 * @field x: número para cálculo imediato
 */
typedef struct sieves_buffer buffer_t, *BUFFER;

struct sieves_buffer {
    int id;
    lint reg;
    int x;
};

/// vetor de buffers internos para cada sieve
BUFFER mainbuffer;

/// variável de controle do loop da thread principal
int iterator;

/// variável para geração dos números a serem testados
int number;

/**
 * Cria um novo vetor do tipo buffer_t.
 *
 * Aloca dinamicamente um vetor de tamanho 'size' preenchido com zeros.
 *
 * @param size: tamanho do novo buffer.
 * @return novo buffer
 */
BUFFER newsievebuffer(int size);

/**
 * Função que é executada como thread de resultados.
 *
 * Acessa o buffer de resposta e exibe seu conteúdo.
 *
 * @param arg: NULL
 * @return nothing
 */
void* res_thread(void *arg);

/**
 * Função que é executada como thread de cálculo.
 *
 * Acessa campos específicos no buffer e faz os cálculos necessários
 * para determinar se o número gerado pela thread principal é primo.
 *
 * @param arg: endereço da posição no buffer a qual a sieve pode acessar.
 * @return nothing
 */
void* sieve(void *arg);

#endif
