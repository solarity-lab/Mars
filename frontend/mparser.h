#ifndef MPARSER_H
#define MPARSER_H

#include "mlexer.h"
#include "mtoken.h"
#include "mast.h"

#include <string.h>
#include <stdlib.h>
   
struct mparser {
	struct mlexer* lexer;
	struct mtoken* token;
	struct mtoken* next;
};

#define EXPECTED(t) parser_expected(parser, t)

#define parser_next_token(parser) (parser->token = nexttoken(parser->lexer))
#define parser_lookahead(parser) (parser->next = lookahead(parser->lexer))

#define pline(parser) (parser->lexer->line)
#define prow(parser) (parser->lexer->row)
#define pfile(parser) (parser->lexer->file)

struct mparser* mparser_new(struct mlexer* l);

int parser_free(struct mparser* parser);

int parser_expected(struct mparser *parser, enum TOKEN type);

struct mast* mparser_statement(struct mparser* parser);
struct mast* mparser_parse(struct mparser* parser);

// block
struct mast* mparser_block(struct mparser* parser);
struct mast* mparser_if_block(struct mparser* parser);
struct mast* mparser_else_block(struct mparser* parser);

// expression
struct mast* mparser_factor(struct mparser* parser);
struct mast* mparser_primary(struct mparser* parser);
struct mast* mparser_term(struct mparser* parser);
struct mast* mparser_expr(struct mparser* parser);
struct mast* mparser_condition(struct mparser* parser);

// statement
struct mast* mparser_if_statement(struct mparser* parser);
struct mast* mparser_while_statement(struct mparser* parser);
struct mast* mparser_function_declaration(struct mparser* parser);
struct mast* mparser_return_statement(struct mparser* parser);
struct mast* mparser_assign(struct mparser* parser);

// excel
struct mast* mparser_PRINT(struct mparser* parser);
struct mast* mparser_MOVE_TO(struct mparser* parser);
struct mast* mparser_WRITE(struct mparser* parser);
struct mast* mparser_CREATE(struct mparser* parser);

// special
struct mast* mparser_function_call(struct mparser* parser, struct mast* callee);

#endif // MPARSER
