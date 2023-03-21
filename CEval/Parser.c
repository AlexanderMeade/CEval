#include "./include/Parser.h"
#include "./Vector.c"
#include <stdlib.h>
#include "./ASTNode.c"

#define Parser_next(parser, steps) \
    parser->index += steps;\
    parser->curr_token =  (Token*)Vector_get(parser->tokens, parser->index); 

#define Parser_getNext(parser) (Token*)Vector_get(parser->tokens, parser->index+1)




static Parser *Parser_init(Vector *tokens){
    Parser *parser = calloc(1, sizeof(Parser));
    parser->tokens = tokens;
    parser->curr_token = (Token*)Vector_get(parser->tokens, 0);
    parser->index = 0;
    parser->inExpr = 0;
    return parser;
}

static void Parser_error(Parser *parser){
    printf("\nPARSER ERROR AT INDEX %zu", parser->index);
    exit(1);
}

static void Parser_eat(Parser *parser, Token_types type){
    if(parser->index + 1 >= parser->tokens->size){
        return;
    }
//    printf("\ntest at Parser_eat\n");
    if (parser->curr_token->type == type){
        Parser_next(parser, 1);
    }else{
        printf("\nERROR AT PARSER_EAT\n");
        Parser_error(parser);
    }
}


static ASTNode *Parser_factor(Parser *parser){
  //  printf("\ntest at Parser_factor\n");
    Token *tok = parser->curr_token;
    printf("\nParser_factor |  val : %s | %s", tok->stringValue, Token_types_map[tok->type]);
    switch(tok->type){
        case TT_NUMBER:
            Parser_eat(parser, tok->type);
            return ASTNode_init(tok);
        case TT_SYMBOL:
            Parser_eat(parser, tok->type);
            return ASTNode_init(tok);
        case TT_MINUS:
            Parser_eat(parser, tok->type);
            return ASTNode_BinOp_init(NULL, Parser_factor(parser),tok);
        case TT_NOT: 
            Parser_eat(parser, tok->type);
            return ASTNode_BinOp_init(NULL, Parser_expr(parser),tok);
        case TT_BW_NOT: 
            Parser_eat(parser, tok->type);
            return ASTNode_BinOp_init(NULL, Parser_expr(parser),tok);
        case TT_LPAREN:
            Parser_eat(parser, TT_LPAREN);
            ASTNode *node = Parser_expr(parser);
            Parser_eat(parser, TT_RPAREN);
            return node;
        
    }     

    printf("\nASTNODE_factor HAS RETURNED A NULL RESULT\n");
    exit(1);
    return NULL;
}

static ASTNode *Parser_term(Parser *parser){
    //printf("\ntest at Parser_term\n");'
    ASTNode *node = Parser_factor(parser);
    
    while(Token_isTerm(parser->curr_token->type)){
        Token *tok = parser->curr_token;
        switch(tok->type){
            case TT_MULT:
            case TT_DIV:
            case TT_MOD:
            case TT_BW_LEFT:
            case TT_BW_RIGHT:
            case TT_BW_AND:
            case TT_BW_OR:
            case TT_BW_XOR:
                Parser_eat(parser, tok->type);
                break;

        }
        node = ASTNode_BinOp_init(node, Parser_factor(parser), tok);
    }
    return node;
}

static ASTNode *Parser_expr(Parser *parser){
    //printf("\ntest at Parser_expr\n");
    ASTNode *node = Parser_term(parser);


    while(Token_isOp(parser->curr_token->type)){
        Token *tok = parser->curr_token;

        switch(tok->type){
            case TT_PLUS:
                Parser_eat(parser, tok->type);
                break;
            case TT_DOUBLEEQUAL:
            case TT_NOTEQUAL:
            case TT_LESSTHAN:
            case TT_GREATERTHAN:
            case TT_LESSTHANOREQUAL:
            case TT_GREATEROREQUAL:
                Parser_eat(parser, tok->type);
                parser->inExpr = 1;
                node = ASTNode_BinOp_init(node,  Parser_expr(parser),tok);

                continue;
            case TT_MINUS:
                Parser_eat(parser, tok->type);
                break;
            case TT_EQUAL:
                Parser_eat(parser, tok->type);
                node = ASTNode_BinOp_init(node, Parser_expr(parser), tok);
                continue;


            case TT_OR:
            case TT_AND:

                if(parser->inExpr){
                    parser->inExpr = 0;
                    return node; 
                }
                Parser_eat(parser, tok->type);
                node = ASTNode_BinOp_init(node,  Parser_expr(parser),tok);
                continue;
 


        }
        node = ASTNode_BinOp_init(node, Parser_term(parser), tok);
    }
    return node;
}


ASTNode *Parser_parse(Vector *tokens){
    printf("\ntest at Parser_parse\n");
    ASTNode *node = Parser_expr(Parser_init(tokens));
    printf("\nend at Parser_parse\n");
    return node;
}

void PrintNodes(ASTNode *node, int again){
        
    ASTNode_print(node);
    if(node){
        PrintNodes(node->left,1);
        PrintNodes(node->right,1);
    }

}






