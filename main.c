#include "sieve.h"
// github.com/limahrc/sieve


/// constante do número de threads
#define THREAD_NUM 8

int main(int argc, char *argv[]) {

    /// número limite passado pelo usuário
    int limit;

    /* leitura e tratamento dos parâmetros passados via linha de comando */
    if (argc < 2) {
        puts("Nenhum parâmetro passado via linha de comando.");
        printf("Insira o valor para n: ");
        scanf("%i", &limit);
    } else limit = atoi(argv[1]);

    // declarando vetor de threads e thread de resultado
    pthread_t threads[THREAD_NUM], resth;

    /* Inicialização de variáveis globais */
    number = 2;
    mainbuffer = newsievebuffer(THREAD_NUM);

    /* loop de controle principal */
    while (number < limit+1) {

        // definindo o id da sieve
        mainbuffer[iterator].id = iterator;

        // inserindo número na rede de sieves
        mainbuffer[iterator].x = number;

        // criando thread e iniciando sua execução
        pthread_create(&threads[iterator], NULL, sieve, &mainbuffer[iterator]);

        // esperando que a thread criada finalize sua execução e a encerra
        pthread_join(threads[iterator], NULL);

        // cria e executa a thread de resultados
        pthread_create(&resth, NULL, res_thread, NULL);

        // espera o término da execução e encerra a thread
        pthread_join(resth, NULL);
    }

    return 0;
}
