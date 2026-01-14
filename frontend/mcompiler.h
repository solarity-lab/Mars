#ifndef MCOMPILER_H
#define MCOMPILER_H

#include <stdlib.h>
#include <string.h>

#include "menvi.h"
#include "mast.h"
#include "mcode.h"

struct loop_stack {
    int break_label;
    int continue_label;
};

struct mcompiler {
    int address_counter;
    int label_counter;

    struct loop_stack ls[1024];
    int ls_size;
    
    int is_in_function;
    int is_in_class;
    int is_in_local;
};

#define CHECKIFNULL(ast) if (!ast) return NULL_CODE;

#define make_address(comp) ((comp)->address_counter++)
#define make_label(comp) ((comp)->label_counter++)

struct mcompiler* mcompiler_new(void);

int push_loop(struct mcompiler *comp, struct loop_stack ls);
struct loop_stack get_top_loop(struct mcompiler *comp);
int pop_loop(struct mcompiler *comp);

struct mcode* mcompiler_compile_ast_program(struct mast* ast, struct mcompiler *compiler, struct menvi *envi);

// compile general
struct mcode* mcompiler_compile(struct mast* ast, struct mcompiler *compiler, struct menvi *envi);

// binary expression
struct mcode* mcompiler_compile_ast_binary_expression(struct mast* ast, struct mcompiler *compiler, struct menvi *envi);

// expression
struct mcode* mcompiler_compile_ast_literal(struct mast* ast, struct mcompiler *compiler, struct menvi *envi);
struct mcode* mcompiler_compile_ast_identifer(struct mast* ast, struct mcompiler *compiler, struct menvi *envi);
struct mcode* mcompiler_compile_ast_function_call(struct mast* ast, struct mcompiler *compiler, struct menvi *envi);

// block & body
struct mcode* mcompiler_compile_ast_body(struct mast* ast, struct mcompiler *compiler, struct menvi *envi);
struct mcode* mcompiler_compile_ast_block(struct mast* ast, struct mcompiler *compiler, struct menvi *envi);

// statement
struct mcode* mcompiler_compile_ast_assign(struct mast* ast, struct mcompiler *compiler, struct menvi *envi);

struct mcode* mcompiler_compile_ast_if(struct mast* ast, struct mcompiler *compiler, struct menvi *envi);

struct mcode* mcompiler_compile_ast_while(struct mast* ast, struct mcompiler *compiler, struct menvi *envi);

struct mcode* mcompiler_compile_ast_function_declaration(struct mast* ast, struct mcompiler *compiler, struct menvi *envi);

struct mcode* mcompiler_compile_ast_return(struct mast* ast, struct mcompiler *compiler, struct menvi *envi);

// special
struct mcode* mcompiler_compile_block(struct mast** block, int block_size, struct mcompiler *compiler, struct menvi *envi);

#endif // MCOMPILER_H
