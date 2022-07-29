COLLATZ: begin

public RETURN

IN: extern
EVEN_OR_ODD: extern

secao texto
input IN

LOOP:
jmp EVEN_OR_ODD

RETURN:
jmpz DIV_BY_TWO
jmp MULT_3_AND_ADD_1

BYEBYE:
stop

DIV_BY_TWO:
load IN
div TWO
store IN
output IN
sub ONE
jmpz BYEBYE
jmp LOOP

MULT_3_AND_ADD_1:
load IN
mul THREE
add ONE
store IN
output IN
jmp LOOP

secao dados
OUT: space
ONE: const 1
TWO: const 2
THREE: const 3

end