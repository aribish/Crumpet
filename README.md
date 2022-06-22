# Crumpet
A rudimentary programming language utilizing a few single-character instructions.

## Compiling
To compile the interpreter source code, you must have make installed on your system. Run 'make 
crumpet' or 'make crumpet-db' (for the debugger version).

## Syntax
>: Pushs the value of the *a register into the *stack.
<: Pops the top value of the stack into the a register.
+: Adds the values of the a and b registers and put the result in the a register.
-: Subtracts the values of the a and b registers and put the result in the a register.
~: Swaps the values of the a and b register.
#: Prints the integer value of the a register followed by a newline to stdout.
!: Prints the character value of the a register to stdout.
*: Sets a *bookmark.
=: Jumps to the last bookmark if the a and b registers are equal.
(: Marks the start of a *comment.
): Marks the end of a comment.

* Crumpet has two registers, named the a and b registers. The a register is always initialized to 
1, and the b register is initially set to 0.

* To implement loops, Crumpet uses bookmarks. Bookmarks are not actual instructions, they just mark
spots in the code to be referred to by the comparison instruction ('='). This instruction compares
the values of the a and b registers. If they are equal, the interpreter jumps to the code directly 
after the bookmark. If they are not equal, the instruction does nothing.

* Crumpet has basic multiline comments, marked with standard parentheses. Anything inside of the 
parenthesis will not be interpreted by the interpreter.

## Interpreter Use
interpreter|interpreter-db [file]
