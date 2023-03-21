#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./include/Evaluator.h"


/*
 *          evaluator NOTES
 *          (#) - side note this annotates a number
 *
 *          LFB(#) - Functions
 *          LFE(#) - Declerations
 *          LC(#) - Strings
 *
 *
 *
 * 
 * */

Evaluator *Evaluator_init(Vector *nodes){
    Evaluator *evaluator = calloc(1, sizeof(Evaluator));
    evaluator->nodes = nodes;

    return evaluator;
}



static int Evaluator_isMathOperator(ASTNode *ast){
    switch(ast->token->type){
        case TT_DIV:
        case TT_PLUS:
        case TT_MINUS:
        case TT_MULT:
        case TT_MOD:
        case TT_BW_AND:
        case TT_BW_OR:
        case TT_BW_RIGHT:
        case TT_BW_LEFT:
        case TT_BW_NOT:
        case TT_BW_XOR:
            return 1;
    }
    return 0;
}

static int Evaluator_isBooleanOperator(ASTNode *ast){
    switch(ast->token->type){
        case TT_NOT:
        case TT_DOUBLEEQUAL:
        case TT_NOTEQUAL:
        case TT_LESSTHAN:
        case TT_LESSTHANOREQUAL:
        case TT_GREATERTHAN:
        case TT_GREATEROREQUAL:
        case TT_AND:
        case TT_OR:
            return 1;
    }
    return 0;
}




static double Evaluator_parseBinaryExpression(ASTNode *ast){
    if(!ast)
        return -1;

    double left;
    double right;

    if(ast->left){
        if(ast->left->token->type != TT_NUMBER){
            left = Evaluator_parseBinaryExpression(ast->left);
        }else if (ast->left->token->type == TT_NUMBER){
            left = ast->left->token->data.value;
        }else if(Evaluator_isBooleanOperator(ast->left)){
            left = Evaluator_parseBooleanExpression(ast->left);
        }
    }
    if(ast->right){
        if(ast->right->token->type != TT_NUMBER){
            right = Evaluator_parseBinaryExpression(ast->right); 
        }else if(ast->right->token->type == TT_NUMBER){
            right = ast->right->token->data.value;
        }else if(Evaluator_isBooleanOperator(ast->right)){
            left = Evaluator_parseBooleanExpression(ast->right);
        }
    }


    switch(ast->token->type){
        case TT_DIV:
             printf("\n%f / %f = %f", left, right, left/right);
             return left / right;
        case TT_PLUS:
             printf("\n%f + %f = %f", left, right, left + right);
             return left + right;
        case TT_MINUS:
             printf("\n%f - %f = %f", left, right, left - right);
             return left - right;
        case TT_MULT:
             printf("\n%f * %f = %f", left, right, left * right);
             return left * right;
        case TT_MOD:
             printf("\n%f % %f = %f", left, right, (int)left % (int)right);
             return (float)((int)left % (int)right);

        case TT_BW_AND:
             printf("\n%f & %f = %f", left, right, (float)((int)left & (int)right));
             return (float)((int)left & (int)right);
        case TT_BW_OR:

             printf("\n%f | %f = %f", left, right, (float)((int)left | (int)right));
             return (float)((int)left | (int)right);
        case TT_BW_RIGHT:

             printf("\n%f >> %f = %f", left, right, (float)((int)left >> (int)right));
             return (float)((int)left >> (int)right);
        case TT_BW_LEFT:

             printf("\n%f << %f = %f", left, right, (float)((int)left << (int)right));
             return (float)((int)left << (int)right);
        case TT_BW_NOT:

             printf("\n~%f = %f", left, right, (float)(~(int)right));
             return (float)(~(int)right);
        case TT_BW_XOR:

             printf("\n%f ^ %f = %f", left, right, (float)((int)left ^ (int)right));
             return (float)((int)left ^ (int)right);

    }
    return 0;
}

static int Evaluator_parseBooleanExpression(ASTNode *ast){
    if(!ast)
        return -1;

    double left;
    double right;
    if(ast->left){
        if(Evaluator_isBooleanOperator(ast->left)){
            left = Evaluator_parseBooleanExpression(ast->left);
        }else if (ast->left->token->type == TT_NUMBER){
            left = ast->left->token->data.value;
        }else if(Evaluator_isMathOperator(ast->left)){
            left = Evaluator_parseBinaryExpression(ast->left);
        }
        
    }
    if(ast->right){
        if(Evaluator_isBooleanOperator(ast->right)){
            right = Evaluator_parseBooleanExpression(ast->right); 
        }else if(ast->right->token->type == TT_NUMBER){
            right = ast->right->token->data.value;
        }else if(Evaluator_isMathOperator(ast->right)){
            right = Evaluator_parseBinaryExpression(ast->right);
        }
    }

    switch(ast->token->type){
        case TT_NOT:
             printf("\n!%f = %d", right, !right);
             return !right;
        case TT_DOUBLEEQUAL:
             printf("\n%f == %f = %d", left, right, left == right);
             return left == right;
        case TT_NOTEQUAL:
             printf("\n%f != %f = %d", left, right, left != right);
             return left != right;
        case TT_LESSTHAN:
             printf("\n%f < %f = %d", left, right, left < right);
             return left < right;
        case TT_LESSTHANOREQUAL:
             printf("\n%f <= %f = %d", left, right, left <= right);
             return left <= right;
        case TT_GREATERTHAN:
             printf("\n%f > %f = %d", left, right, left > right);
             return left > right;
        case TT_GREATEROREQUAL:
             printf("\n%f >= %f = %d", left, right, left >= right);
             return left >= right;
        case TT_AND:
             printf("\n%f && %f = %d", left, right, left && right);
             return left && right;
        case TT_OR:
             printf("\n%f || %f = %d", left, right, left || right);
             return left || right;
    }
    return 0;

}

static void Evaluator_parseAST(Evaluator *evaluator, ASTNode *ast){
    if(!ast)
        return;
    //check root node
    switch(ast->token->type){
        //MathFuncs
        case TT_DIV:
        case TT_MULT:
        case TT_PLUS:
        case TT_MINUS:
        case TT_MOD:
        case TT_BW_AND:
        case TT_BW_OR:
        case TT_BW_XOR:
        case TT_BW_NOT:
        case TT_BW_LEFT:
        case TT_BW_RIGHT:
            printf("\nRESULT : %f\n", Evaluator_parseBinaryExpression(ast));
            break;
        
        case TT_AND:
        case TT_OR:
        case TT_NOT:
        case TT_DOUBLEEQUAL:
        case TT_NOTEQUAL:
        case TT_LESSTHAN:
        case TT_LESSTHANOREQUAL:
        case TT_GREATERTHAN:
        case TT_GREATEROREQUAL:
            printf("\nRESULT : %s\n", Evaluator_parseBooleanExpression(ast) ?"true":"false");
            break;
 
    }
}



void Evaluator_start(Evaluator *evaluator){
    
    for(int i = 0; i < evaluator->nodes->size; i++){
        ASTNode *t = (ASTNode*)Vector_get(evaluator->nodes, i);
        Evaluator_parseAST(evaluator, t);   
    }

    printf("end");
    
}


