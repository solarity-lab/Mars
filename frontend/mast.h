#ifndef MAST_H
#define MAST_H

#include "mtoken.h"
#include "mdebug.h"

enum AST_TYPE {
    AST_PROGRAM,
    AST_BLOCK,
    AST_STATEMENT,
    AST_EXPRESSION,
    AST_BREAK,
    AST_CONTINUE,
    AST_ASSIGNMENT,
    AST_IF,
    AST_ANONYMOUS_FUNCTION,
    AST_WHILE,
    AST_COMPARE_EXPRESSION,
    AST_AND_EXPRESSION,
    AST_RETURN_STATEMENT,
    AST_OR_EXPRESSION,
    AST_STORE_INDEX,
    AST_TRUE,
    AST_FALSE,
    AST_NOT_EXPRESSION,
    AST_FUNCTION_CALL_EXPRESSION,
    AST_FUNCTION_STATEMENT,
    AST_FOR,
    AST_BINARY_EXPRESSION,
    AST_IDENTIFIER,
    AST_LITERAL,
    AST_STRING_EXPRESSION,
    AST_LIST,
    AST_NULL,
};

#define avalueof(a) ((a)->value)
#define alexemeof(a) ((a)->lexeme)
#define atypeof(a) ((a)->type)

struct mast {
    enum AST_TYPE type;
    float value;
    char* lexeme;

    char *parameters[1024];
    int parameter_count;

    struct mast* left;
    struct mast* right;
    enum TOKEN op;

    struct mast* next;
    struct mast* prev;

    struct mast** parent;
    int size;
    int index;

    struct mast** block;
    int block_size;
    int block_index;

    struct mast** arguments;
    int arg_size;
    int arg_index;

    struct mast* callee;

    struct mast* condition;
    struct mast* if_body;
    struct mast* else_body;

    struct mast* body;
    struct mast* expr;
};

struct mast* mast_new(void);

struct mast* mast_init(enum AST_TYPE type, char* lexeme, float value);

void mast_free(struct mast* mast);

int mast_add_child(struct mast* mast, struct mast* child);
int mast_add_block(struct mast* mast, struct mast* child);
int mast_add_argument(struct mast* mast, struct mast* argument);

struct mast* mast_binary_expr(struct mast *left, struct mast *right, enum TOKEN op);

int mast_not_statement(struct mast* mast, int line, int row, char* file);

void mast_print(struct mast* mast);

#endif // MAST_H
