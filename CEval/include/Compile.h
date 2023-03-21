#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "./Vector.h"
#include "./ASTNode.h"
typedef struct {
    Vector *nodes;
   
    char *fileName;
    size_t LFE_Iter; // delceration
    size_t LFB_Iter; // func bodies
    size_t LC_Iter; // strings
    FILE *file;
}Evaluator;

Evaluator *Evaluator_init(Vector *nodes, char *fileName);


static double Evaluator_parseBinaryExpression(ASTNode *ast);

static void Evaluator_parseAST(Evaluator *eval, ASTNode *ast);

void Evaluator_end(Evaluator *eval);

void Evaluator_start(Evaluator *eval);


#endif
