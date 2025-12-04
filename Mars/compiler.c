#include "compiler.h"

struct Code* 
CompileProgram
(struct Ast *ast, struct Environment *env) {
    struct Code *code = CodeNew();

    for (int i = 0; i < ast->size; i++) {
        struct Ast *child = ast->children[i];
        struct Code *child_code = Compile(child, env);
        CodeAddCode(code, child_code);
    }

    return code;
}

struct Code* 
Compile
(struct Ast *ast, struct Environment *env) {
    switch (ast->type) {
        case AST_PROGRAM:
            return CompileProgram(ast, env);
        case AST_BINARY_EXPRESSION:
            return CompileBinaryExpression(ast, env);
        case AST_IDENTIFER:
            return CompileIdentifier(ast, env);
        case AST_LITERAL:
            return CompileNumberLiteral(ast, env);
        case AST_PRINT:
            return CompilePrintStatement(ast, env);
        case AST_PUSH:
            return CompilePushStatement(ast, env);
        case AST_POP:
            return CompilePopStatement(ast, env);
        default:
            return NULL_CODE;
    }
}

struct Code* 
CompileBinaryExpression
(struct Ast *ast, struct Environment *env) {
    struct Code *code = CodeNew();

    CodeAddCode(code, Compile(ast->left, env));
    CodeAddCode(code, Compile(ast->right, env));

    switch (ast->op) {
        case PLUS:
            CodeAdd(code, OP_ADD);
            break;
        case MINUS:
            CodeAdd(code, OP_SUB);
            break;
        case MUL:
            CodeAdd(code, OP_MUL);
            break;
        case DIV:
            CodeAdd(code, OP_DIV);
            break;
        default:
            break;
    }

    return code;
}

struct Code* 
CompileIdentifier
(struct Ast *ast, struct Environment *env) {
    
}

struct Code* 
CompileNumberLiteral
(struct Ast *ast, struct Environment *env) {
    struct Code *code = CodeNew();
    CodeAdd(code, OP_PUSH);

    byte value_bytes[4];
    float value = ast->value;
    memcpy(value_bytes, &value, 4);
    CodeAdd(code, value_bytes[0]);
    CodeAdd(code, value_bytes[1]);
    CodeAdd(code, value_bytes[2]);
    CodeAdd(code, value_bytes[3]);

    return code;
}

struct Code* 
CompilePrintStatement
(struct Ast *ast, struct Environment *env) {
    struct Code *code = CodeNew();
    CodeAddCode(code, Compile(ast->expression, env));
    CodeAdd(code, OP_PRINT);
    return code;
}

struct Code* 
CompilePushStatement
(struct Ast *ast, struct Environment *env) {
    struct Code *code = CodeNew();
    CodeAddCode(code, Compile(ast->expression, env));
    CodeAdd(code, OP_PUSH);
    return code;
}

struct Code* 
CompilePopStatement
(struct Ast *ast, struct Environment *env) {
    struct Code *code = CodeNew();
    CodeAdd(code, OP_POP);
    return code;
}
