# sieve
Trabalho da disciplina de Sistemas Operacionais cujo objetivo é implementar uma variação distribuída do Crivo de
Erastóstenes (em inglês, Sieve of Eratosthenes), um algoritmo simples e prático para
encontrar números primos no intervalo entre 2 e um dado valor limite n.

O programa é testado da seguinte maneira:
./trab1 n onde n é o número máximo que deve ser testado.

A thread de resultados imprime as informações sobre cada número testado, EM
ORDEM. Assim, se o número for primo ele é indicado como tal, juntamente com
a sieve aonde ele ficou armazenado. Se o número não for primo, essa informação ̧
também é impressa. Dessa forma, por exemplo, se executarmos
./trab1 10, teremos como resposta no terminal:

2 is prime (stored in sieve 0)  
3 is prime (stored in sieve 1)  
4 divided by 2 at sieve 0  
5 is prime (stored in sieve 2)  
6 divided by 2 at sieve 0  
7 is prime (stored in sieve 3)  
8 divided by 2 at sieve 0  
9 divided by 3 at sieve 1  
10 divided by 2 at sieve 0  
