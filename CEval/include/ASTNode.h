#ifndef ASTNODE_H
#define ASTNODE_H

#include "./Token.h"

char *ASTNodeType_map[] = {
    "ANT_Undefined",
    "ANT_Plus",
    "ANT_Minus",
    "ANT_Mult",
    "ANT_Div",
    "ANT_UnaryMinus",
    "ANT_Number"
};

typedef enum {
    ANT_Undefined = 0,
    ANT_Plus = 1,
    ANT_Minus = 2,
    ANT_Mult = 3,
    ANT_Div = 4,
    ANT_UnaryMinus = 5,
    ANT_Number = 6
}ASTNodeType; 

typedef struct ASTNode_struct{
    Token *token;
    struct ASTNode_struct *left;
    struct ASTNode_struct *right;
}ASTNode;

ASTNode *ASTNode_init(Token *token);

ASTNode *ASTNode_BinOp_init(ASTNode *left, ASTNode *right, Token *token);

void ASTNode_print(ASTNode *node);

#endif
