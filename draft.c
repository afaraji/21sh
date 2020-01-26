

// pipe_expression == expression |* expression*
// expression == cmd args* (operator_exp filename)*
// cmd == word
// args == 1 or more space separated words
// operator_exp == int* operator int*
// int == integer 1, 2 or 3 (need verif)
// operator == >, >> , ...
// filename == word

// dependancy pipe or operator 1st
// $ () {} ?
// $ == ^{* var_exp* }*
// var_exp == [a-zA-Z_][0-9a-zA-Z_]*
