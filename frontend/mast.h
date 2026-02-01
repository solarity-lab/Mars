#ifndef MAST_H
#define MAST_H

#include "mtoken.h"
#include "mdebug.h"

enum AST_TYPE {
    /* program */
    AST_PROGRAM,
    AST_BLOCK,
    AST_STATEMENT,

    /* assignment */
    AST_ASSIGNMENT,
    AST_LET,
    
    /* control statement */
    AST_IF,
    AST_WHILE,
    AST_FOR,

    /* function */
    AST_FUNCTION,
    AST_RETURN,

    /* expression */
    AST_BINARY_EXPRESSION,
    AST_COMPARE_EXPRESSION,
    AST_NOT_EXPRESSION,
    AST_AND_EXPRESSION,
    AST_OR_EXPRESSION,
    
    /* primary */
    AST_IDENTIFIER,
    AST_LITERAL,
    AST_FUNCTION_CALL,

    /* special */
    AST_PRINT,
    AST_NULL,

    /* grid */
    AST_MOVE_CURSOR_TO,
    AST_GRID_WRITE,
    AST_GRID_READ,
    AST_GRID_ERASE,
    AST_GRID_CREATE,
    AST_GRID_CLOSE,
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

    struct mast** opers;
    enum TOKEN* ops;
    int opers_size;
    int opers_cap;
    int ops_size;
    int ops_cap;

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

    struct mast* row_expr;
    struct mast* column_expr;

    int line;
    int row;
    char* file;
};

struct mast* mast_new(void);

struct mast* mast_init(enum AST_TYPE type, char* lexeme, float value);

void mast_free(struct mast* mast);

int mast_add_child(struct mast* mast, struct mast* child);
int mast_add_block(struct mast* mast, struct mast* child);
int mast_add_argument(struct mast* mast, struct mast* argument);
int mast_add_opers(struct mast* mast, struct mast* oper);
int mast_add_ops(struct mast* mast, enum TOKEN op);

struct mast* mast_binary_expr(struct mast *left, struct mast *right, enum TOKEN op);

int merror_not_statement(struct mast* mast, int line, int row, char* file);

int is_ast_expr(struct mast* mast);

void mast_print(struct mast* mast);

#endif // MAST_H
