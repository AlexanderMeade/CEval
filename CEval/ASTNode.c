#include "./include/ASTNode.h"
#include "./Token.c"
#include <stdlib.h>

ASTNode *ASTNode_init(Token *token){
    ASTNode *astNode = calloc(1, sizeof(ASTNode));
    astNode->token = token;

    astNode->left = NULL;
    astNode->right = NULL;
    return astNode;
}

ASTNode *ASTNode_BinOp_init(ASTNode *left, ASTNode *right, Token *token){
    ASTNode *astNode = calloc(1, sizeof(ASTNode));
    astNode->token = token;
    astNode->left = left;
    astNode->right = right;
    return astNode;

}


/*
 *  function calls are cyan
 *  code blocks are yellow
 *  Node information will be green
 * */

void ASTNode_print(ASTNode *node){
    printf("\n\n");
    if(!node){
        return;
    }
    switch(node->token->type){
        case TT_NUMBER:
        case TT_SYMBOL:
            return;
    }
    printf("\033[0;35m");
    printf("\nNode->value : %f\nNode->type : %s\nNode->stringValue : %s\n", node->token->data.value, Token_types_map[node->token->type], node->token->stringValue);
    printf("\033[0m");
    switch(node->token->type){
        case TT_NUMBER:
            return;
    }

    if(!node->left){
        printf("\033[0;31m");

        printf("\n\tNode->left is NULL");
        printf("\033[0m");
    }else {
        printf("\033[0;32m");

        printf("\n\tNode->left->value : %f\n\tNode->left->type : %s\n\tNode->stringValue : %s\n", node->left->token->data.value, Token_types_map[node->left->token->type], node->left->token->stringValue);
        printf("\033[0m");
        
    }
    printf("\n");
    if(!node->right){
            printf("\033[0;31m");
            printf("\n\tNode->right is NULL");
            printf("\033[0m");
    }else {
            printf("\033[0;32m");
            printf("\n\tNode->right->value : %f\n\tNode->right->type : %s\n\tNode->stringValue : %s\n", node->right->token->data.value, Token_types_map[node->right->token->type], node->right->token->stringValue);

            printf("\033[0m");
            

    }
    
}
