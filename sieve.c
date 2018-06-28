//
// Created by limahrc on 09/06/18.
// github.com/limahrc/sieve
//

#include "sieve.h"

/// constante booleana para representação de um número primo
#define PRIME true

/// constante booleana para representação de um número não-primo
#define NOT_PRIME false

/// buffer de resposta
static char str[64];

BUFFER newsievebuffer(int size) {
    return (BUFFER) calloc((size_t) size, sizeof(buffer_t));
}

/**
 * Gerencia o laço da thread principal
 */
static inline void manage_sieves() {
    number++;                   // incrementa o gerador de números a serem testados
    iterator = 0;               // retorna o indice do vetor de sieves para 0
}

/**
 * Escreve no buffer de resposta a mensagem de resultado dos cálculos da sieve
 *
 * @param mybuffer: buffer interno da sieve que chamou a função
 * @param divisor: número pelo qual ocorreu a divisão de x, caso x seja não-primo
 * @param is_prime: valor booleano para determinar a mensagem a ser escrita
 */
static inline void send_result_message(BUFFER mybuffer, int divisor, bool is_prime) {
    if (is_prime) sprintf(str, "%i is prime (stored in sieve %i)\n", mybuffer->x, mybuffer->id);
    else {
        if (divisor==0) divisor = getinfo(mybuffer->reg);
        sprintf(str, "%i divided by %i at sieve %i\n", mybuffer->x, divisor, mybuffer->id);
    }
}

void* res_thread(void *arg) {
    if (iterator == 0)
        printf("%s", str);
    pthread_exit(NULL);
}

void* sieve(void *arg) {
    // conversão de tipo para buffer_t*
    BUFFER mybuffer = (BUFFER) arg;

    // verifica se o campo de números registrados está vazio
    if (mybuffer->reg == NULL || getinfo(mybuffer->reg) == 0) {

        // insere o número atual no buffer de registrados
        insend(&mybuffer->reg, newnode(mybuffer->x));

        // classifica o número atual como primo e envia para buffer de resultado
        send_result_message(mybuffer, 0, PRIME);

    } else { // caso o buffer de registrados não esteja vazio

        // verifica se o número atual é divisível pelo número registrado
        if (mybuffer->x % getinfo(mybuffer->reg) != 0) {

            // verifica se a sieve atual é a sieve 7 (ultima do anel)
            if (mybuffer->id == 7) {

                // aloca um nó de lista encadeada para auxiliar
                node *aux = getprox(mybuffer->reg);
                while(aux != NULL){
                    // verifica se o número atual é divisível pelo número no nó atual do
                    // buffer de registrados
                    if (mybuffer->x % getinfo(aux) != 0){
                        // avança um nó na lista
                        aux = getprox(aux);
                    } else { // caso não seja divisível
                        // classifica o número atual como não-primo e envia para buffer de resultado
                        send_result_message(mybuffer, getinfo(aux), NOT_PRIME);
                        break;
                    }
                }
                // caso se atinja o fim da lista encadeada, o número é primo e registrado no buffer
                if (aux == NULL) {
                    // aloca um novo nó e o insere no final da lista encadeada
                    insend(&mybuffer->reg, newnode(mybuffer->x));
                    send_result_message(mybuffer, 0, PRIME);
                }
                /* caso o número atual não seja divisível pelo número registrado e a sieve
                atual não seja a 7*/
            } else {
                // escreve o número atual no buffer da próxima sieve
                mainbuffer[mybuffer->id + 1].x = mybuffer->x;
                // avança o iterador para que a próxima sieve seja criada
                iterator++;
                // finaliza a execução da sieve atual
                pthread_exit(NULL);
            }
        }
        // caso o número atual seja divisível pelo número registrado, classifica como não-primo
        else send_result_message(mybuffer, 0, NOT_PRIME);
    }
    // chama a função de controle do loop principal
    manage_sieves();
    // finaliza a execução da sieve atual
    pthread_exit(NULL);
}

