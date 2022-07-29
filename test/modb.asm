EVEN_OR_ODD: begin

public IN
public EVEN_OR_ODD

RETURN: extern

secao texto
load IN
div TWO
mul TWO
sub IN
jmpn FOUND_ODD
load ZERO
jmp RETURN

FOUND_ODD:
load ONE
jmp RETURN

secao dados
TWO: const 2
ONE: const 1
ZERO: const 0
IN: space

end