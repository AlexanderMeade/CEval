#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "./Vector.h"
#include "./ASTNode.h"
typedef struct {
    Vector *nodes;   
}Evaluator;

Evaluator *Evaluator_init(Vector *nodes);

static int Evaluator_isMathOperator(ASTNode *ast);

static int Evaluator_isBooleanOperator(ASTNode *ast);

static double Evaluator_parseBinaryExpression(ASTNode *ast);

static int Evaluator_parseBooleanExpression(ASTNode *ast);

static void Evaluator_parseAST(Evaluator *eval, ASTNode *ast);

void Evaluator_start(Evaluator *eval);


#endif
