                                        ⍼
----------------------------------------------------------------------------------------

#Prefix Infix Postfix
    Prefix notation : + 1 2
    Infix notation : 1 + 2
    Postfix notation : 1 2 +

#Reverse Polish Notation (RPN)
    Reverse Polish Notation (RPN) implies transforming the infix expression in a postfix expression and then evaluating it from left to right. 1 + 2*3 is transformed into 1 2 3 * +. You go from left to right until you find an operator, evaluate the expression and then replace it in the stack.

#Abstract Syntax Tree
    Abstract Syntax Tree (AST) is an abstract representation of an expression, with inner nodes representing operators and leafs representing numbers.

    example:
        +
       / \
      1   *
         / \
        2   3

#definition for parsing
    EXP    -> TERM EXP1
    EXP1   -> + TERM EXP1 | 
          - TERM EXP1 | 
          epsilon
    TERM   -> FACTOR TERM1
    TERM1  -> * FACTOR TERM1 | 
          / FACTOR TERM1 | 
          epsilon
    FACTOR -> ( EXP ) | - EXP | number




fizzBuzz(n) = {                                  -| creates the function fizzBuzz
    if(n % 5 == 0 && n % 3 == 0): _printf("fizz")
    elif(n % 5 == 0) : _printf("buzz")
    elif(n % 3 == 0) : _printf("fizz")
    else : _printf("%d", n)

}
