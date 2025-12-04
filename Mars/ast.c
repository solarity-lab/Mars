#include "ast.h"
#include <stdlib.h>

struct Ast*
AstNew(void) {
    struct Ast *ast = (struct Ast*) malloc(sizeof(struct Ast));

    ast->type = AST_NONE;
    ast->value = 0;
    ast->lexeme = NULL;
    
    ast->expression = NULL;

    ast->left = NULL;
    ast->right = NULL;
    ast->op = NONE;
    ast->size = 0;
    ast->capacity = MAX_STATEMENT_SIZE;
    ast->children = calloc(MAX_STATEMENT_SIZE, sizeof(struct Ast*));

    return ast;
}

struct Ast*
AstAddChildren
(struct Ast *ast, struct Ast *children) {
     if (ast->size >= ast->capacity) {
        ast->capacity *= 2;
        ast->children = realloc(ast->children, ast->capacity * sizeof(struct Ast*));
    }
  

    ast->children[ast->size++] = children;
    return ast;
}

struct Ast*
AstMakeBinaryExpression
(struct Ast* left, struct Ast *right, enum TOKEN_TYPE op) {
    struct Ast* ast = AstNew();

    ast->type = AST_BINARY_EXPRESSION;

    ast->left = left;
    ast->right = right;
    ast->op = op;
    
    return ast;
}       

struct Ast*
AstSetParent
(enum AST_TYPE type, float value, char* lexeme) {
    struct Ast* ast = AstNew();

    ast->type = type;
    ast->value = value;
    ast->lexeme = lexeme;

    return ast;
}
