#ifndef PARSER_H
#define PARSER_H

#include "./Vector.h"
#include "./ASTNode.h"
#include "./Token.h"
typedef struct {
    Vector *tokens;
    Token *curr_token;
    size_t index;
    size_t inExpr;
}Parser;

static Parser *Parser_init(Vector *tokens);

static void Parser_error(Parser *parser);

static void Parser_eat(Parser *parser, Token_types type);


static ASTNode *Parser_factor(Parser *parser);

static ASTNode *Parser_term(Parser *parser);

static ASTNode *Parser_expr(Parser *parser);


ASTNode *Parser_parse(Vector *tokens);

void PrintNodes(ASTNode *node, int again);
#endif
