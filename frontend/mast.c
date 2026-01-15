#include "mast.h"
#include "mtool.h"

struct mast* mast_new(void) {
    struct mast* mast = malloc(sizeof(struct mast));

    mast->type = AST_NULL;
    mast->value = 0.0f;
    mast->lexeme = NULL;

    mast->block_index = 0;
    mast->block_size = 1024;
    mast->block = calloc(1024, sizeof(struct mast*));

    mast->index = 0;
    mast->size = 1024;
    mast->parent = calloc(1024, sizeof(struct mast*));

    mast->arg_index = 0;
    mast->arg_size = 1024;
    mast->arguments = calloc(1024, sizeof(struct mast*));

    mast->body = NULL;
    mast->expr = NULL;

    mast->condition = NULL;
    mast->if_body = NULL;
    mast->else_body = NULL;

    mast->left = NULL;
    mast->right = NULL;
    mast->op = T_NONE;

    mast->next = NULL;
    mast->prev = NULL;

    return mast;
}

struct mast* mast_init(enum AST_TYPE type, char* lexeme, float value) {
    struct mast* mast = mast_new();

    mast->type = type;
    mast->value = value;
    mast->lexeme = lexeme;

    return mast;
}

void mast_free(struct mast* node) {
    if (!node) return;

    if (node->block) {
        for (size_t i = 0; i < node->block_index; i++) {
            mast_free(node->block[i]);
        }
        free(node->block);
    }

    if (node->left) {
        mast_free(node->left);
    }

    if (node->right) {
        mast_free(node->right);
    }

    if (node->lexeme) {
        free(node->lexeme);
    }

    if (node->parent) {
        free(node->parent);
    }

    free(node);
}

int mast_add_child(struct mast* mast, struct mast* child) {
    ensure_capacity((void**)&mast->parent, &mast->size, sizeof(struct mast*), mast->index);
    mast->parent[mast->index++] = child;
    return 0;
}   

int mast_add_block(struct mast* mast, struct mast* child) {
    ensure_capacity((void**)&mast->block, &mast->block_size, sizeof(struct mast*), mast->block_index);
    mast->block[mast->block_index++] = child;
    return 0;
}

int mast_add_argument(struct mast* mast, struct mast* argument) {
    ensure_capacity((void**)&mast->arguments, &mast->arg_size, sizeof(struct mast*), mast->arg_index);
    mast->arguments[mast->arg_index++] = argument;
    return 0;
}

struct mast* mast_binary_expr(struct mast *left, struct mast *right, enum TOKEN op) {
    struct mast* mast = mast_new();

    mast->type = AST_BINARY_EXPRESSION;

    mast->left = left;
    mast->right = right;
    mast->op = op;

    return mast;
}

void mast_print(struct mast* mast) {
    printf("%s\n", mast->lexeme);
}

int is_ast_expr(struct mast* mast) {
    enum AST_TYPE type = mast->type;
    if (type == AST_BINARY_EXPRESSION 
        || type == AST_FUNCTION_CALL
        || type == AST_IDENTIFIER
        || type == AST_LITERAL
        || type == AST_NULL) {
        return 1;
    }
    return 0;
}

int mast_not_statement(struct mast* mast, int line, int row, char* file) {
    if (!mast) return 0;

    if (is_ast_expr(mast)) {
        return 1;
    }

    error_at("Expected expression", file, line, row);
    return 0;
}