#include "mcompiler.h"
#include "mtool.h"

int push_loop(struct mcompiler *comp, struct loop_stack ls) {
    comp->ls[comp->ls_size++] = ls;
    return 0;
}

int pop_loop(struct mcompiler *comp) {
    struct loop_stack nls;
    comp->ls[comp->ls_size - 1] = nls;
    comp->ls_size--;
    return 0;
}

struct mcompiler* mcompiler_new(void) {
    struct mcompiler* comp = (struct mcompiler*) malloc(sizeof(struct mcompiler));
    comp->address_counter = 50;
    comp->label_counter = 50;
    
    comp->is_in_function = 0;
    comp->is_in_class = 0;
    comp->is_in_local = 0;

    comp->ls_size = 0;

    return comp;
}

struct loop_stack get_top_loop(struct mcompiler *comp) {
    return comp->ls[comp->ls_size - 1];
}

struct mcode* mcompiler_compile_ast_program(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    CHECKIFNULL(ast);

    struct mcode* program = NULL_CODE;

    envi->global = envi;
    envi->is_global = 1;
    
    for (int i = 0; i < ast->index; i++) {
        struct mast* child = ast->parent[i];
        struct mcode *code = mcompiler_compile(ast->parent[i], compiler, envi);

        INSERT(program, code);

        if (is_ast_expr(child)) {
            PUSH(program, OKPOP);
        }
    }

    PUSH(program, OKHALT);
    return program;
}

struct mcode* mcompiler_compile(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    CHECKIFNULL(ast);

    switch (ast->type) {
        case AST_BINARY_EXPRESSION: 
            return mcompiler_compile_ast_binary_expression(ast, compiler, envi);
        
        case AST_COMPARE_EXPRESSION: 
            return mcompiler_compile_ast_compare_expression(ast, compiler, envi);
        
        case AST_IDENTIFIER: 
            return mcompiler_compile_ast_identifer(ast, compiler, envi);
        
        case AST_LITERAL: 
            return mcompiler_compile_ast_literal(ast, compiler, envi);
        
        case AST_ASSIGNMENT:
            return mcompiler_compile_ast_assign(ast, compiler, envi);
        
        case AST_IF: 
            return mcompiler_compile_ast_if(ast, compiler, envi);
        
        case AST_WHILE: 
            return mcompiler_compile_ast_while(ast, compiler, envi);
        
        case AST_FUNCTION_CALL: 
            return mcompiler_compile_ast_function_call(ast, compiler, envi);
        
        case AST_FUNCTION: 
            return mcompiler_compile_ast_function_declaration(ast, compiler, envi);
        
        case AST_RETURN: 
            return mcompiler_compile_ast_return(ast, compiler, envi);
        
        case AST_PRINT: 
            return mcompiler_compile_ast_PRINT(ast, compiler, envi);
        
        case AST_MOVE_CURSOR_TO: 
            return mcompiler_compile_ast_MOVE_TO(ast, compiler, envi);
        
        case AST_GRID_WRITE: 
            return mcompiler_compile_ast_WRITE(ast, compiler, envi);
        
        case AST_GRID_CREATE: 
            return mcompiler_compile_ast_CREATE(ast, compiler, envi);
        
        case AST_NOT_EXPRESSION: 
            return mcompiler_compile_ast_not(ast, compiler, envi);
        
        case AST_OR_EXPRESSION: 
            return mcompiler_compile_ast_or(ast, compiler, envi);
        
        case AST_AND_EXPRESSION: 
            return mcompiler_compile_ast_and(ast, compiler, envi);
        
        case AST_GRID_CLOSE: {
            struct mcode* code = NULL_CODE;
            PUSH(code, CCCLOSE);
            return code;
        }
        case AST_GRID_READ: {
            struct mcode* code = NULL_CODE;
            PUSH(code, CCREAD);
            return code;
        }
    }

    error_at("Unknown AST node type in compiler", "<main>", 0, 0);
    return NULL_CODE;
}


struct mcode* mcompiler_compile_ast_binary_expression(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    CHECKIFNULL(ast);
    
    struct mcode* code = NULL_CODE;

    struct mcode* left = mcompiler_compile(ast->left, compiler, envi);
    struct mcode* right = mcompiler_compile(ast->right, compiler, envi);

    INSERT(code, left);
    INSERT(code, right);

    switch (ast->op) {
        case T_PLUS:  PUSH(code, OKADD); break;
        case T_MINUS: PUSH(code, OKSUB); break;
        case T_DIV:   PUSH(code, OKDIV); break;
        case T_TIMES: PUSH(code, OKMUL); break;
        case T_MOD:   PUSH(code, OKMOD); break;
    }

    return code;
}

struct mcode* mcompiler_compile_ast_compare_expression(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    CHECKIFNULL(ast);

    struct mcode* code = NULL_CODE;

    int j = 0;
    int i = 0;
    for (;i < ast->opers_size - 1; i++, j++) {
        struct mcode* left  = mcompiler_compile(ast->opers[i], compiler, envi);
        struct mcode* right = mcompiler_compile(ast->opers[i + 1], compiler, envi);

        INSERT(code, left);
        INSERT(code, right);

        enum TOKEN op = ast->ops[j];

        switch (op) {
            case T_GT:  PUSH(code, OKGT); break;
            case T_GTE: PUSH(code, OKGTE); break;
            case T_LT:  PUSH(code, OKLT); break;
            case T_LTE: PUSH(code, OKLTE); break;
            case T_NEQ: PUSH(code, OKNEQ); break;
            case T_EQ:  PUSH(code, OKEQ); break;

            default:
                error_type(__Mstring("Unknown operator '%d'", op), COMPILER_ERR);
        }

        if (i > 0) PUSH(code, OKAND);
    }

    return code;
}

struct mcode* mcompiler_compile_ast_literal(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    CHECKIFNULL(ast);

    struct mcode* code = NULL_CODE;

    float value = ast->value;
    
    unsigned char float_code[4];
    memcpy(float_code, &value, sizeof(float));
    
    PUSH(code, OKPUSH_FLOAT);

    PUSH(code, float_code[0]);
    PUSH(code, float_code[1]);
    PUSH(code, float_code[2]);
    PUSH(code, float_code[3]);

    return code;
}

struct mcode* mcompiler_compile_ast_identifer(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    CHECKIFNULL(ast);

    struct scope* scope = fine_scope(envi, ast->lexeme);

    if (!scope) {
        error_type(__Mstring("Undefined variable '%s'", ast->lexeme), COMPILER_ERR);
    }

    struct mcode* code = NULL_CODE;

    if (scope->is_closure) {
        PUSH(code, OKLOAD_CLOSURE);
    } else if (scope->is_local) {
        PUSH(code, OKLOAD_LOCAL);
    } else {
        PUSH(code, OKLOAD);
    }

    PUSH(code, scope->address);

    return code;
}

struct mcode* mcompiler_compile_ast_assign(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    CHECKIFNULL(ast);

    struct mcode* code = mcompiler_compile(ast->expr, compiler, envi);
    
    struct scope* scope = scope_set(compiler->address_counter++, ast->lexeme);
    scope = store_scope(envi, scope);

    if (!scope) {
        return NULL_CODE;
    }

    if (scope->is_closure) {
        PUSH(code, OKSTORE_CLOSURE);
    } else if (scope->is_local) {
        PUSH(code, OKSTORE_LOCAL);
    } else {
        PUSH(code, OKSTORE);
    }

    PUSH(code, scope->address);

    return code;
}

struct mcode* mcompiler_compile_ast_if(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    CHECKIFNULL(ast);

    struct mcode* code = NULL_CODE;

    struct mcode* condition = mcompiler_compile(ast->condition, compiler, envi);
    INSERT(code, condition);

    int else_label = make_label(compiler);
    int end_label = make_label(compiler);

    PUSH(code, OKJMP_IF_FALSE);
    PUSH(code, else_label);

    struct mcode* if_body = mcompiler_compile_ast_block(ast->if_body, compiler, envi);
    INSERT(code, if_body);

    PUSH(code, OKJMP);
    PUSH(code, end_label);

    PUSH(code, OKADDRESS);
    PUSH(code, else_label);

    if (ast->else_body) {
        struct mcode* else_body = mcompiler_compile_ast_block(ast->else_body, compiler, envi);
        INSERT(code, else_body);
    }

    PUSH(code, OKADDRESS);
    PUSH(code, end_label);
    return code;
}

struct mcode* mcompiler_compile_ast_while(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    CHECKIFNULL(ast);

    struct mcode* code = NULL_CODE;

    int start_label = make_label(compiler);
    int end_label = make_label(compiler);

    PUSH(code, OKADDRESS);
    PUSH(code, start_label);

    struct mcode* condition = mcompiler_compile(ast->condition, compiler, envi);
    INSERT(code, condition);

    PUSH(code, OKJMP_IF_FALSE);
    PUSH(code, end_label);

    struct mcode* body = mcompiler_compile_ast_block(ast->body, compiler, envi);
    INSERT(code, body);

    PUSH(code, OKJMP);
    PUSH(code, start_label);

    PUSH(code, OKADDRESS);
    PUSH(code, end_label);

    return code;
}

struct mcode* mcompiler_compile_ast_function_declaration(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    CHECKIFNULL(ast);
    
    struct mcode* code = NULL_CODE;

    int func_address = compiler->address_counter++;
    int arg_count = ast->parameter_count;

    struct scope* func_scope = scope_set(func_address, ast->lexeme);
    func_scope = store_scope(envi, func_scope);

    if (envi->is_function) {
        PUSH(code, OKMAKE_CLOSURE);
    } else {
        PUSH(code, OKMAKEFUNC);
    }

    PUSH(code, arg_count);

    for (int i = 0; i < arg_count; i++) {
        struct scope* arg_scope = scope_set(compiler->address_counter++, ast->parameters[i]);
        arg_scope = store_scope(envi, arg_scope);

        PUSH(code, OKMAKE_ARGS);
        PUSH(code, arg_scope->address);
    }

    PUSH(code, OKSTART_FUNC);

    struct mcode* func_body = mcompiler_compile_ast_body(ast->body, compiler, envi);
    INSERT(code, func_body);

    if (envi->is_function) {
        PUSH(code, OKEND_CLOSURE);
    } else {
        PUSH(code, OKEND_FUNC);
    }

    if (func_scope->is_closure) {
        PUSH(code, OKSTORE_CLOSURE);
    } else if (func_scope->is_local) {
        PUSH(code, OKSTORE_LOCAL);
    } else {
        PUSH(code, OKSTORE);
    }

    PUSH(code, func_address);

    return code;
}

struct mcode* mcompiler_compile_ast_function_call(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    CHECKIFNULL(ast);

    struct mcode* code = NULL_CODE;

    struct mcode* calle = mcompiler_compile(ast->callee, compiler, envi);
    struct mcode* argument = mcompiler_compile_block(ast->arguments, ast->arg_index, compiler, envi);
    
    INSERT(code, argument);
    INSERT(code, calle);

    PUSH(code, OKCALL);
    
    return code;
}

struct mcode* mcompiler_compile_ast_return(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    CHECKIFNULL(ast);

    struct mcode* code = mcompiler_compile(ast->expr, compiler, envi);
    PUSH(code, OKRETURN);
    return code;
}

// special
struct mcode* mcompiler_compile_block(struct mast** block, int block_size, struct mcompiler *compiler, struct menvi *envi) {
    CHECKIFNULL(block);

    struct mcode* block_code = NULL_CODE;

    for (int i = 0; i < block_size; i++) {
        struct mast* child = block[i];

        struct mcode *code = mcompiler_compile(block[i], compiler, envi);

        INSERT(block_code, code);

        if (is_ast_expr(child)) {
            PUSH(block_code, OKPOP);
        }
    }

    return block_code;
}

// block & body

struct mcode* mcompiler_compile_ast_body(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    CHECKIFNULL(ast);

    struct menvi* local_envi = menvi_new();
    
    local_envi->prev = envi;
    local_envi->is_function = 1;
    local_envi->global = envi->global;

    return mcompiler_compile_block(ast->block, ast->block_index, compiler, local_envi);
}

struct mcode* mcompiler_compile_ast_block(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    CHECKIFNULL(ast);

    return mcompiler_compile_block(ast->block, ast->block_index, compiler, envi);
}

// control

struct mcode* mcompiler_compile_ast_PRINT(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    CHECKIFNULL(ast);

    struct mcode* code = mcompiler_compile(ast->expr, compiler, envi);
    PUSH(code, OKPRINT);
    return code;
}

struct mcode* mcompiler_compile_ast_WRITE(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    CHECKIFNULL(ast);

    struct mcode* code = mcompiler_compile(ast->expr, compiler, envi);
    PUSH(code, CCWRITE);
    return code;
}

struct mcode* mcompiler_compile_ast_MOVE_TO(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    CHECKIFNULL(ast);

    struct mcode* code = NULL_CODE;

    INSERT(code, mcompiler_compile(ast->row_expr, compiler, envi));
    INSERT(code, mcompiler_compile(ast->column_expr, compiler, envi));

    PUSH(code, CCMOVE_TO);

    return code;
}

struct mcode* mcompiler_compile_ast_CREATE(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    CHECKIFNULL(ast);

    struct mcode* code = NULL_CODE;

    INSERT(code, mcompiler_compile(ast->row_expr, compiler, envi));
    INSERT(code, mcompiler_compile(ast->column_expr, compiler, envi));

    PUSH(code, CCCREATE);

    return code;
}

struct mcode* mcompiler_compile_ast_and(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    struct mcode* code = NULL_CODE;

    struct mcode* left = mcompiler_compile(ast->left, compiler, envi);
    struct mcode* right = mcompiler_compile(ast->right, compiler, envi);

    INSERT(code, left);
    INSERT(code, right);

    PUSH(code, OKAND);
    return code;
}

struct mcode* mcompiler_compile_ast_or(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    struct mcode* code = NULL_CODE;

    struct mcode* left = mcompiler_compile(ast->left, compiler, envi);
    struct mcode* right = mcompiler_compile(ast->right, compiler, envi);

    INSERT(code, left);
    INSERT(code, right);

    PUSH(code, OKOR);
    return code;
}

struct mcode* mcompiler_compile_ast_not(struct mast* ast, struct mcompiler *compiler, struct menvi *envi) {
    struct mcode* code = mcompiler_compile(ast->expr, compiler, envi);
    PUSH(code, OKNOT);
    return code;    
}