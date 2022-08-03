Trabalho de Software Básico

Nome: Gabriel de Sousa Vieira
Matricula: 16/0006350

configuração de ambiente: g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0

instruções de compilação:

<h2> Montador </h2>
Instruções de compilação:
Na pasta ./montador
g++ *.cpp -o montador

Intruções de uso: 
Para pre-processar.
"./montador -p myprogram.asm saida.pre"

Para montar:
"./montador -o myprogram.pre saida.o"

Obs.: O montador utiliza da instrução MUL no lugar de MULT, para alterar acesse a tabela auxfunction.h

<h2> Ligador </h2>
Instruções de compilação:
Na pasta ./ligador
g++ *.cpp -o ligador

"./ligador myprog1.o myprog2.o"