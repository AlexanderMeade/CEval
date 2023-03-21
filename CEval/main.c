#include <stdio.h>
#include "./Lexer.c"
#include "./FileHandler.c"
#include "./Parser.c"
#include ".\Evaluator.c"
//Make code blocks work

int main(int argc, char **argv){
    printf("most recent build\n");
    if(argc < 2){
        printf("\nNOT ENOUGH ARGS");
        return 1;

    }
    char *filename = argv[1];
    if(!file_exists(filename)){
        printf("\nFILE DOESN'T EXIST");
        return 1;
    }

    char *content = read_file(filename);
    size_t end = 0;
    while(content[end] != '\0')
        end+=1;
    register Lexer *lexer = Lexer_init(content, end-1);
    Lexer_start(lexer);
    
    printf("\n\n\n\n\n\nLEXER TOKEN DUMP \n\n\n\n\n\n\n");

    for(int i = 0; i < lexer->tokens->size; i++){
        Token *tok = (Token*)Vector_get(lexer->tokens, i);
        printf("\ntok %zu | %s\n\tvalue : %s", i, Token_types_map[tok->type], tok->stringValue);        
    } 
    Vector *tokens = Token_splitAt(lexer->tokens, TT_NEWLINE);


    for(int j = 0; j < tokens->size; j++){
        Vector *vect =((Vector*)Vector_get(tokens, j));
        for(int i = 0; i < vect->size; i++){
            Token *tok = (Token*)Vector_get(vect, i);
             printf("\ntok %zu | %s\n\tvalue : %d", i, Token_types_map[tok->type], tok->data.value);
                }

    } 
    printf("\n-------------- multilined statements test start --------------\n");
    Vector *nodes = Vector_init(sizeof(ASTNode));
    printf("\n\n\n TOKENS SIZE %zu\n\n\n", tokens->size);
    for(int j = 0; j < tokens->size; j++){
        //goes over ever token in token array
        Vector *toks = Vector_get(tokens, j);
        //register Parser *parser = Parser_init(lexer->tokens);

        ASTNode *node = Parser_parse(toks);
        Vector_push(nodes, (void*)node);

    }
    
    printf("\033[0;32m");
    printf("\n============================================================PARSER PHASE ENDED ============================================================\n");
    printf("\033[0m");   


    for(int i = 0; i < nodes->size; i++){ 
        printf("\033[0;35m");
        printf("\n========================================================================================================================\n");
        printf("\033[0m");   

        PrintNodes(Vector_get(nodes, i), 0);  
         

        printf("\nend");  
    }
    printf("\n\npre compiler test");
    
    Evaluator *evaluator = Evaluator_init(nodes);
     
    Evaluator_start(evaluator);
    return 0;
}



