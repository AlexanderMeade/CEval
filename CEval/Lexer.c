#include "./include/Lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>


#define Lexer_back(lexer, steps)\
    lexer->index -= steps;\
    lexer->curr_char = lexer->content[lexer->index];

#define Lexer_getNext(lexer)\
    lexer->content[lexer->index+1]


Lexer *Lexer_init(char *content, size_t end){
    Lexer *lexer= calloc(1, sizeof(Lexer));
    lexer->end = end;
    lexer->tokens = Vector_init(sizeof(Token));
    lexer->index = 0;
    lexer->content = content;
    lexer->curr_char = lexer->content[lexer->index];   
    return lexer;
}

void Lexer_skipWhiteSpace(Lexer *lexer){
    while(lexer->curr_char == '\t' || lexer->curr_char == ' '){
        Lexer_next(lexer);
    }

}

static Token *Lexer_parseNumber(Lexer *lexer, size_t isNeg){
    char *value = malloc(sizeof(char));
    size_t size = 0;
    int isFloat = 0;

    while ((isdigit(lexer->curr_char) || lexer->curr_char == '.'&&lexer->curr_char != '\0')){
        //printf("%c", lexer->curr_char);
        if(lexer->curr_char == '.' && isFloat == 0){
            isFloat = 1;
        }
        /*else if(lexer->curr_char == '.' && isFloat == 1){
            char *str = calloc(1, sizeof(char) * 2);
            str[0] = lexer->curr_char;
            str[1] = '\0';
            return token_init(str, ERROR, lexer->line, lexer->colmn, lexer->index, lexer->index);
        }*/
        //value[size] = '\0';
  //      printf("%c", lexer->curr_char); 
        value[size] = lexer->curr_char;
        size += 1;
        value = realloc(value, sizeof(char) * size + 1);
        value[size] = '\0';

         
        Lexer_next(lexer);
    }
    Lexer_back(lexer, 1);
    //printf("test : %s", value);
    return Token_initNumber(isNeg?atof(value) * -1:atof(value), value);
}

static Vector *Lexer_collectUpTo(Lexer *lexer, char character, size_t skipNewLines){
    Vector *tokens = Vector_init(sizeof(Token));
    while(lexer->curr_char != character){
        //printf("\ntok -> %c", lexer->curr_char);

        
        if(lexer->curr_char == '\t' || lexer->curr_char == ' '){
            Lexer_skipWhiteSpace(lexer);
            continue;
        }
        if(lexer->curr_char == '\n' && skipNewLines){
            Lexer_next(lexer);
            continue;
        }
        if(lexer->curr_char == '\0'){

            break;
        }
        Vector_push(tokens, (void*)Lexer_parse(lexer));
        Lexer_next(lexer);
    }
    return tokens;
}

static Token *Lexer_parse(Lexer *lexer){
    switch(lexer->curr_char){
        case '\t':
            Lexer_skipWhiteSpace(lexer);
            return Lexer_parse(lexer);
        case ' ':
            Lexer_skipWhiteSpace(lexer);
            return Lexer_parse(lexer);
        case '+':
            return Token_initSymbol(TT_PLUS, '+', "+");
        case '-':
            if(Lexer_getNext(lexer) == '|'){
                Lexer_next(lexer);
                while(lexer->curr_char != '\n'){
                    Lexer_next(lexer);
                }
                Lexer_next(lexer);
                return Lexer_parse(lexer);
            }
            return Token_initSymbol(TT_MINUS, '-', "-");
        case '*':
            return Token_initSymbol(TT_MULT, '*', "*");
        case '/':
            return Token_initSymbol(TT_DIV, '/', "/");
        case '\0':
            return Token_initSymbol(TT_EOT, '\0', "\0");
        case '(':
            return Token_initSymbol(TT_LPAREN, '(', "(");
        case ')':
            return Token_initSymbol(TT_RPAREN, ')', ")");
        case '!':
            if(Lexer_getNext(lexer) == '='){
                Lexer_next(lexer);
                return Token_initSymbol(TT_NOTEQUAL, '!', "!=");
            }
            return Token_initSymbol(TT_NOT, '!', "!");
        case '=':
            if(Lexer_getNext(lexer) == '='){
                Lexer_next(lexer);
                return Token_initSymbol(TT_DOUBLEEQUAL, '=', "==");
            }
            return Token_initSymbol(TT_EQUAL, '=', "=");
        case '&':
            if(Lexer_getNext(lexer) == '&'){
                Lexer_next(lexer);
                return Token_initSymbol(TT_AND, '&', "&&");
            }
            return Token_initSymbol(TT_BW_AND, '&', "&");
        case '|':
            if(Lexer_getNext(lexer) == '|'){
                Lexer_next(lexer);
                return Token_initSymbol(TT_OR, '|', "||");
            }
            return Token_initSymbol(TT_BW_OR, '|', "||");
        case '<':
            switch(Lexer_getNext(lexer)){
                case '=':
                    Lexer_next(lexer);
                    return Token_initSymbol(TT_LESSTHANOREQUAL, '<', "<=");
                case '<':
                    Lexer_next(lexer);
                    return Token_initSymbol(TT_BW_LEFT, '<', "<<");
            }

            return Token_initSymbol(TT_LESSTHAN, '<', "<");

        case '>':
            switch(Lexer_getNext(lexer)){
                case '=':
                    Lexer_next(lexer);
                    return Token_initSymbol(TT_GREATEROREQUAL, '>', ">=");
                case '>':
                    Lexer_next(lexer);
                    return Token_initSymbol(TT_BW_RIGHT, '>', ">>");
            }

            return Token_initSymbol(TT_GREATERTHAN, '>', ">");

        case '^':
            return Token_initSymbol(TT_BW_XOR, '^', "^");
        case '~':
            return Token_initSymbol(TT_BW_NOT, '~', "~");
        case '%':
            return Token_initSymbol(TT_MOD, '%', "%");

        case '\n':
            return Token_initSymbol(TT_NEWLINE, 'n', "new line");

    }
    if(isdigit(lexer->curr_char) || lexer->curr_char == '.'){
        return Lexer_parseNumber(lexer, 0);
    }

    printf("\n\n\nRETURN LEXER CURR CHAR ERROR : %c", lexer->curr_char); 
    char str[] = {lexer->curr_char,'\0'};
    return Token_initSymbol(TT_ERROR, lexer->curr_char, str);
}

static void Lexer_next(Lexer *lexer){

    lexer->index += 1;
    lexer->curr_char = lexer->content[lexer->index];
    
}

void Lexer_start(Lexer *lexer){
    //printf("\ntest4\n\n\n")
    while(lexer->curr_char != '\0' && lexer->index < lexer->end){
        //printf("%c", lexer->curr_char);
        Token *tok = Lexer_parse(lexer);
         
        if(tok->type != TT_ERROR){
            Vector_push(lexer->tokens, (void*)tok);
        }
        Lexer_next(lexer);

    }
    
    for(int i = 0; i < lexer->tokens->size; i++){
        Token *tok = (Token*)Vector_get(lexer->tokens, i);
        printf("\ntok %d | %s\n\tvalue : %f", i, Token_types_map[tok->type], tok->data.value);
        printf("\033[0;34m");
        printf("\033[0m");
    }
    printf("\033[0;32m");
    printf("\n============================================================LEXER PHASE ENDED ============================================================\n");
    printf("\033[0m");   
}
