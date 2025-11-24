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

void AstPrint(struct Ast *ast) {
    if (!ast) return;

    switch (ast->type) {
        case AST_LITERAL:
            printf("Literal: %f\n", ast->value);
            break;
        case AST_IDENTIFER:
            printf("Identifier: %s\n", ast->lexeme);
            break;
        case AST_BINARY_EXPRESSION:
            printf("Binary Expression: ");
            if (ast->left) AstPrint(ast->left);
            if (ast->right) AstPrint(ast->right);
            printf("Operator: %d\n", ast->op);
            break;
        case AST_PUSH:
            printf("Push: ");
            if (ast->expression) AstPrint(ast->expression);
            break;
        case AST_POP:
            printf("Pop\n");
            break;
        case AST_PRINT:
            printf("Print: ");
            if (ast->expression) AstPrint(ast->expression);
            break;
        case AST_PROGRAM:
            printf("Program with %d children:\n", ast->size);
            for (int i = 0; i < ast->size; i++) {
                AstPrint(ast->children[i]);
            }
            break;
        case AST_NONE:
            printf("None\n");
            break;
        default:
            printf("Unknown AST node\n");
            break;
    }
}
