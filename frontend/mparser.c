#include "mparser.h"

int parser_expected(struct mparser *p, enum TOKEN type) {
    if (p->token->type != type) {
        char* mess = malloc(256);
        sprintf(mess, "Expected token %d but got %d", type, p->token->type);
        error_at(mess, pfile(p), pline(p), prow(p));
        return -1;
    }
    return 0;
}

struct mparser* mparser_new(struct mlexer* lexer) {
    struct mparser* parser = (struct mparser*) malloc(sizeof(struct mparser));
    parser->lexer = lexer;
    parser->token = NULL;
    parser->next = NULL;
    return parser;
}

int parser_free(struct mparser* parser) {
    free(parser);
    return 0;
}

struct mast* mparser_statement(struct mparser* parser) {
    if (ptok_t(parser) == T_IDENTIFIER) {
        parser->next = lookahead(parser->lexer);
        if (parser->next->type == T_ASSIGN) return mparser_assign(parser);

        return mparser_condition(parser);
    }

    else if (ptok_t(parser) == T_IF) 
        return mparser_if_statement(parser);
    else if (ptok_t(parser) == T_WHILE)
        return mparser_while_statement(parser);
    else if (ptok_t(parser) == T_FUNC)
        return mparser_function_declaration(parser);
    else if (ptok_t(parser) == T_RETURN)
        return mparser_return_statement(parser);

    else if (ptok_t(parser) == T_PRINT)
        return mparser_PRINT(parser);
    else if (ptok_t(parser) == T_MOVE) 
        return mparser_MOVE_TO(parser);
    else if (ptok_t(parser) == T_WRITE)
        return mparser_WRITE(parser);
    else if (ptok_t(parser) == T_CREATE)
        return mparser_CREATE(parser);

    else if (ptok_t(parser) == T_CLOSE) {
        parser_next_token(parser);
        return mast_init(AST_GRID_CLOSE, NULL, 0);
    }

    else if (ptok_t(parser) == T_READ) {
        parser_next_token(parser);
        return mast_init(AST_GRID_READ, NULL, 0);
    }

    return mparser_logical(parser);
}

struct mast* mparser_parse(struct mparser* parser) {
    struct mast* program = mast_new();
    program->type = AST_PROGRAM;
    parser_next_token(parser);
    while (ptok_t(parser) != T_EOF) {
        struct mast* statement = mparser_statement(parser);
        mast_add_child(program, statement);
    }
    return program;
}

struct mast* mparser_block(struct mparser* parser) {
    struct mast* block = mast_new();

    block->type = AST_BLOCK;

    parser_expected(parser, T_DO);
    parser_next_token(parser);

    while (ptok_t(parser) != T_END) {
        struct mast* statement = mparser_statement(parser);
        mast_add_block(block, statement);
    }

    return block;
}

struct mast* mparser_else_block(struct mparser* parser) {
    struct mast* block = mast_new();

    block->type = AST_BLOCK;

    parser_expected(parser, T_ELSE);
    parser_next_token(parser);

    while (ptok_t(parser) != T_END) {
        struct mast* statement = mparser_statement(parser);
        mast_add_block(block, statement);
    }

    return block;
}

struct mast* mparser_if_block(struct mparser* parser) {
    struct mast* block = mast_new();

    block->type = AST_BLOCK;

    parser_expected(parser, T_THEN);

    parser_next_token(parser);

    while (ptok_t(parser) != T_END && ptok_t(parser) != T_ELSE) {
        struct mast* statement = mparser_statement(parser);
        mast_add_block(block, statement);
    }

    return block;
}

struct mast* mparser_logical(struct mparser* parser) {
    return mparser_or(parser);
}

struct mast* mparser_primary(struct mparser* parser) {
    struct mast* node = mparser_factor(parser);
    parser_lookahead(parser);

    if (parser->next->type == T_LPAREN) {
        parser_next_token(parser);
        return mparser_function_call(parser, node);
    }

    return node;
}

struct mast* mparser_factor(struct mparser* parser) {
    if (ptok_t(parser) == T_NUMBER) 
        return mast_init(AST_LITERAL, parser->token->lexeme, parser->token->value);
    if (ptok_t(parser) == T_IDENTIFIER) 
        return mast_init(AST_IDENTIFIER, parser->token->lexeme, parser->token->value);
    if (ptok_t(parser) == T_LPAREN) {
        parser_next_token(parser);
        struct mast* expr = mparser_expr(parser);
        parser_expected(parser, T_RPAREN);
        return expr;
    }

    if (ptok_t(parser) == T_NOT) {
        return mparser_not(parser);
    }
    
    error_at("Unexpected token", pfile(parser), pline(parser), prow(parser));
    return NULL;
}

struct mast* mparser_not(struct mparser* parser) {
    if (ptok_t(parser) != T_NOT) {
        return mparser_condition(parser);
    }

    struct mast* node = mast_init(AST_NOT_EXPRESSION, NULL, 0);

    parser_next_token(parser);

    node->expr = mparser_statement(parser);
    
    merror_not_statement(node->expr, pline(parser), prow(parser), pfile(parser));

    return node;
}

struct mast* mparser_and(struct mparser* parser) {
    struct mast* node = mparser_not(parser);

    while (ptok_t(parser) == T_AND) {
        struct mast* and_node = mast_init(AST_AND_EXPRESSION, NULL, 0);

        parser_next_token(parser);

        and_node->left = node;
        and_node->right = mparser_parse(parser);

        merror_not_statement(and_node->right, pline(parser), prow(parser), pfile(parser));

        node = and_node;

        return node;
    }

    return node;
}

struct mast* mparser_or(struct mparser* parser) {
    struct mast* node = mparser_and(parser);

    while (ptok_t(parser) == T_OR) {
        struct mast* or_node = mast_init(AST_OR_EXPRESSION, NULL, 0);

        parser_next_token(parser);

        or_node->left = node;
        or_node->right = mparser_parse(parser);

        merror_not_statement(or_node->right, pline(parser), prow(parser), pfile(parser));

        node = or_node;

        return node;
    }

    return node;
}

struct mast* mparser_term(struct mparser* parser) {
    struct mast* left = mparser_primary(parser);
    parser_next_token(parser);
    while (ptok_t(parser) == T_TIMES || ptok_t(parser) == T_DIV || ptok_t(parser) == T_MOD) {
        enum TOKEN op = ptok_t(parser);
        parser_next_token(parser);
        struct mast* right = mparser_primary(parser);
        left = mast_binary_expr(left, right, op);
        parser_next_token(parser);
    }
    return left;
}

struct mast* mparser_expr(struct mparser* parser) {
    struct mast* left = mparser_term(parser);
    while (ptok_t(parser) == T_PLUS || ptok_t(parser) == T_MINUS) {
        enum TOKEN op = ptok_t(parser);
        parser_next_token(parser);
        struct mast* right = mparser_term(parser);
        left = mast_binary_expr(left, right, op);
    }
    return left;
}
    
struct mast* mparser_condition(struct mparser* parser) {
    struct mast* node = mast_init(AST_COMPARE_EXPRESSION, NULL, 0);
    
    struct mast* first = mparser_expr(parser);

    mast_add_opers(node, first);

    int has_op = 0;

    while (ptok_t(parser) == T_GT 
    || ptok_t(parser) == T_GTE 
    || ptok_t(parser) == T_LT 
    || ptok_t(parser) == T_LTE
    || ptok_t(parser) == T_NEQ
    || ptok_t(parser) == T_EQ) 
    
    {
        has_op = 1;

        enum TOKEN op = ptok_t(parser);
        mast_add_ops(node, op);

        parser_next_token(parser);

        struct mast* oper = mparser_expr(parser);

        mast_add_opers(node, oper);
    }

    if (!has_op) return first;

    return node;
}

struct mast* mparser_assign(struct mparser* parser) {
    struct mast* node = mast_init(AST_ASSIGNMENT, NULL, 0);

    parser_expected(parser, T_IDENTIFIER);
    node->lexeme = parser->token->lexeme; 
    
    parser_next_token(parser);
    parser_expected(parser, T_ASSIGN);

    parser_next_token(parser);
    
    struct mast* value = mparser_statement(parser);
    merror_not_statement(value, pline(parser), prow(parser), pfile(parser));
    node->expr = value;
    return node;
}

// statement
struct mast* mparser_if_statement(struct mparser* parser) {
    struct mast* if_node = mast_init(AST_IF, NULL, 0);

    parser_expected(parser, T_IF);

    parser_next_token(parser);
    if_node->condition = mparser_statement(parser);

    merror_not_statement(if_node->condition, pline(parser), prow(parser), pfile(parser));

    if_node->if_body = mparser_if_block(parser);

    if (ptok_t(parser) == T_ELSE) {
        if_node->else_body = mparser_else_block(parser);
    }

    parser_expected(parser, T_END);
    parser_next_token(parser);

    return if_node;   
}

struct mast* mparser_while_statement(struct mparser* parser) {
    struct mast* while_node = mast_init(AST_WHILE, NULL, 0);

    parser_expected(parser, T_WHILE);

    parser_next_token(parser);
    while_node->condition = mparser_statement(parser);
    merror_not_statement(while_node->condition, pline(parser), prow(parser), pfile(parser));

    while_node->body = mparser_block(parser);

    parser_expected(parser, T_END);
    parser_next_token(parser);
    return while_node;
}

struct mast* mparser_function_declaration(struct mparser* parser) {
    struct mast* func_node = mast_init(AST_FUNCTION, NULL, 0);
    parser_expected(parser, T_FUNC);
    parser_next_token(parser);
    
    parser_expected(parser, T_IDENTIFIER);

    func_node->lexeme = parser->token->lexeme;

    parser_next_token(parser);
    parser_expected(parser, T_LPAREN);

    parser_next_token(parser);
    while (ptok_t(parser) != T_RPAREN) {
        parser_expected(parser, T_IDENTIFIER);
        func_node->parameters[func_node->parameter_count++] = parser->token->lexeme;

        parser_next_token(parser);
        if (ptok_t(parser) == T_COMMA) {
            parser_next_token(parser);
        }
    }
    
    parser_expected(parser, T_RPAREN);
    parser_next_token(parser);
    func_node->body = mparser_block(parser);

    parser_expected(parser, T_END);
    parser_next_token(parser);
    return func_node;
}

struct mast* mparser_function_call(struct mparser* parser, struct mast* callee) {
    struct mast* call_node = mast_init(AST_FUNCTION_CALL, NULL, 0);

    call_node->callee = callee;

    parser_expected(parser, T_LPAREN);

    parser_next_token(parser);
    while (ptok_t(parser) != T_RPAREN) {
        struct mast* arg = mparser_statement(parser);
        merror_not_statement(arg, pline(parser), prow(parser), pfile(parser));
        mast_add_argument(call_node, arg);

        if (ptok_t(parser) == T_COMMA) {
            parser_next_token(parser);
        }
    }

    parser_expected(parser, T_RPAREN);
    parser_lookahead(parser);

    if (parser->next->type == T_LPAREN) {
        parser_next_token(parser);
        return mparser_function_call(parser, call_node);
    }

    return call_node;
}

struct mast* mparser_return_statement(struct mparser* parser) {
    struct mast* return_node = mast_init(AST_RETURN, NULL, 0);

    parser_expected(parser, T_RETURN);

    parser_next_token(parser);
    return_node->expr = mparser_statement(parser);
    merror_not_statement(return_node->expr, pline(parser), prow(parser), pfile(parser));

    return return_node;
}

struct mast* mparser_PRINT(struct mparser* parser) {
    struct mast* print_node = mast_init(AST_PRINT, NULL, 0);

    parser_expected(parser, T_PRINT);

    parser_next_token(parser);
    print_node->expr = mparser_statement(parser);
    merror_not_statement(print_node->expr, pline(parser), prow(parser), pfile(parser));
    return print_node;
}

struct mast* mparser_MOVE_TO(struct mparser* parser) {
    struct mast* move_to_node = mast_init(AST_MOVE_CURSOR_TO, NULL, 0);

    parser_expected(parser, T_MOVE);

    parser_next_token(parser);

    struct mast* row_expr = mparser_statement(parser);
    merror_not_statement(row_expr, pline(parser), prow(parser), pfile(parser));

    parser_expected(parser, T_COMMA);

    parser_next_token(parser);

    struct mast* col_expr = mparser_statement(parser);
    merror_not_statement(col_expr, pline(parser), prow(parser), pfile(parser));

    move_to_node->row_expr = row_expr;
    move_to_node->column_expr = col_expr;

    return move_to_node;
}

struct mast* mparser_WRITE(struct mparser* parser) {
    struct mast* write_node = mast_init(AST_GRID_WRITE, NULL, 0);

    parser_expected(parser, T_WRITE);

    parser_next_token(parser);
    write_node->expr = mparser_statement(parser);
    merror_not_statement(write_node->expr, pline(parser), prow(parser), pfile(parser));
    return write_node;
}

struct mast* mparser_CREATE(struct mparser* parser) {
    struct mast* write_node = mast_init(AST_GRID_CREATE, NULL, 0);

    parser_expected(parser, T_CREATE);

    parser_next_token(parser);

    struct mast* row_expr = mparser_statement(parser);
    merror_not_statement(row_expr, pline(parser), prow(parser), pfile(parser));

    parser_expected(parser, T_COMMA);

    parser_next_token(parser);

    struct mast* col_expr = mparser_statement(parser);
    merror_not_statement(col_expr, pline(parser), prow(parser), pfile(parser));

    write_node->row_expr = row_expr;
    write_node->column_expr = col_expr;

    return write_node;
}