#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "token.h"

#define MAX_STATEMENT_SIZE 1024

enum AST_TYPE {
    AST_BINARY_EXPRESSION, AST_LITERAL, AST_IDENTIFER, AST_PUSH, AST_POP, AST_PRINT, AST_NONE, AST_PROGRAM
};

struct Ast {
    enum AST_TYPE type;
    float value;
    char* lexeme;
    
    struct Ast *left;
    struct Ast *right;
    enum TOKEN_TYPE op;
    
    struct Ast *expression;

    struct Ast **children;
    int size;
    int capacity;
};

struct Ast*
AstNew(void);

struct Ast*
AstSetParent
(enum AST_TYPE type, float value, char* lexeme);

struct Ast*
AstAddChildren
(struct Ast *ast, struct Ast *children);

struct Ast*
AstMakeBinaryExpression
(struct Ast* left, struct Ast *right, enum TOKEN_TYPE op);

void
AstPrint
(struct Ast *ast);

#endif
