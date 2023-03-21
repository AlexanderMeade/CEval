#include "./include/Token.h"
#include <stdlib.h>
#include <stdio.h>
#define Token_type_str(token) Token_types_map[token->type]

Token *Token_initSymbol(Token_types type, char symbol, char *stringValue){
    Token *token = calloc(1, sizeof(Token));
    token->type = type;
    token->data.symbol = symbol;
    token->stringValue = stringValue;
    return token;
}

Token *Token_initID(Token_types type, char *id){
    Token *token = calloc(1, sizeof(Token));
       
    token->type = type;
    token->stringValue = id;
    return token;
}

Token *Token_initNumber( double num, char *stringValue){
    Token *token = calloc(1, sizeof(Token));
    token->type = TT_NUMBER;
    token->data.value = num;
    token->stringValue = stringValue;
    return token;
}

void Token_printList(Token *token){
    printf("\n\nthis is a test\n\n");
    printf("\033[0m");
    printf("\033[0;38m");


    if(!token){
        printf("\nTOKEN IS NULL");
        return;
    }
    //goes over each token array
    printf("\n----LIST----\n");

    for(int j = 0; j < token->data.args->size; j++){
        //goes over ever token in token array
        Vector *tokens = Vector_get(token->data.args, j);
                printf("\n\t %s INDEX [%d] | ", token->stringValue, j);
        for(int i = 0; i < tokens->size; i++){
            Token *tok = (Token*)(Vector_get(tokens, i));
            printf(" [%s | %s]", tok->stringValue, Token_types_map[tok->type]);
            switch(tok->type){
            } 
        }
    }
    printf("\nLIST END");
    printf("\033[0m");
}
Vector *Token_splitAt(Vector *tokens, Token_types type){
    Token *tok;

    Vector *vects = Vector_init(sizeof(Vector));
    Vector *vtoks = Vector_init(sizeof(Token));

    for(size_t index = 0; index < tokens->size; index++){
        tok = (Token*)Vector_get(tokens, index);

        if(tok->type == type){ //the split point
            if(vtoks->size > 0){
                Vector_push(vects, (void*)vtoks); //push vtoks onto vects
                vtoks = Vector_init(sizeof(Token));
                continue;
            }
            continue;
        }
        //printf("\n\t Token_splitAt currToken : %s", tok->stringValue);
        
        Vector_push(vtoks, (void*)tok);
    }
    if(vtoks->size > 0) {
        Vector_push(vects, (void*)vtoks); //push vtoks onto vects
    }
    return vects;
}



int Token_isToken(char c){
    switch(c){
        case '\t':
            return 1;
        case ' ':
            return 1;
        case '+':
            return 1;
        case '-':

            return 1;
        case '*':
            return 1;
        case '/':
            return 1;
        case '\0':
            return 1;
        case '(':
            return 1;
        case ')':
            return 1;
        case '{':
            return 1;
        case '}':
            return 1;
        case '=':
            return 1;
        case ',':
            return 1;
        case '\n':
            return 1;
        case '"':
            return 1;
    }
    return 0;
}

int Token_isOp(Token_types type){

    switch(type){
        case TT_PLUS:
        case TT_MINUS:
        case TT_EQUAL:
        case TT_LESSTHANOREQUAL:
        case TT_LESSTHAN:
        case TT_GREATERTHAN:
        case TT_GREATEROREQUAL:
        case TT_DOUBLEEQUAL:
        case TT_NOTEQUAL:
        case TT_AND:
        case TT_OR:

        return 1;
    }
    return 0;
}

int Token_isTerm(Token_types type){
    switch(type){
        case TT_MULT:
        case TT_DIV:
        case TT_MOD:
        case TT_BW_LEFT:
        case TT_BW_RIGHT:
        case TT_BW_AND:
        case TT_BW_OR:
        case TT_BW_XOR:
        return 1;
    }
    return 0;
}


