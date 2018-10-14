Programa feito en C que emula o xogo das torres de Hanoi.

Exemplo de compilación:

gcc -Wall torres_hanoi.c -o torres_hanoi

Exemplo de uso:

./torres_hanoi 4

valores validos:
A-B: mover de torre A a torre B, sendo A,B={1,2,3}. Exemplos: 1-2, 3-1,...

fora: acaba o xogo.


Estado actual: 

torre1: 1 2 3 4 

torre2: baleira.

torre3: baleira.

1-3

Estado actual: 

torre1: 2 3 4 0 

torre2: baleira.

torre3: 1 0 0 0 

1-2

Estado actual: 

torre1: 3 4 0 0 

torre2: 2 0 0 0 

torre3: 1 0 0 0 

3-2

Estado actual: 

torre1: 3 4 0 0 

torre2: 1 2 0 0 

torre3: baleira.

1-3

Estado actual: 

torre1: 4 0 0 0 

torre2: 1 2 0 0 

torre3: 3 0 0 0 

2-1

Estado actual: 

torre1: 1 4 0 0 

torre2: 2 0 0 0 

torre3: 3 0 0 0 

2-3

Estado actual: 

torre1: 1 4 0 0 

torre2: baleira.

torre3: 2 3 0 0 

1-3

Estado actual: 

torre1: 4 0 0 0 

torre2: baleira.

torre3: 1 2 3 0 

1-2

Estado actual: 

torre1: baleira.

torre2: 4 0 0 0 

torre3: 1 2 3 0 

3-2

Estado actual: 

torre1: baleira.

torre2: 1 4 0 0 

torre3: 2 3 0 0 

3-1

Estado actual: 

torre1: 2 0 0 0 

torre2: 1 4 0 0 

torre3: 3 0 0 0 

2-1

Estado actual: 

torre1: 1 2 0 0 

torre2: 4 0 0 0 

torre3: 3 0 0 0 

3-2

Estado actual: 

torre1: 1 2 0 0 

torre2: 3 4 0 0 

torre3: baleira.

1-3

Estado actual: 

torre1: 2 0 0 0 

torre2: 3 4 0 0 

torre3: 1 0 0 0 

1-2

Estado actual: 

torre1: baleira.

torre2: 2 3 4 0 

torre3: 1 0 0 0 

3-2

Estado actual: 

torre1: baleira.

torre2: 1 2 3 4 

torre3: baleira.

Acabache.

fora
