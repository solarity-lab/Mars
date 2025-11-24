#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

struct Parser {
    struct Token *token;
    struct Token *next;
    struct Lexer *lexer;
};

struct Parser*
ParserNew(void); 

struct Ast*
ParserParse
(struct Parser *parser);

struct Ast*
ParserParseProgram
(struct Parser *parser);

struct Ast*
ParserParsePrimaryExpression
(struct Parser *parser);

struct Ast*
ParserParseAdditiveExpression
(struct Parser *parser);

struct Ast*
ParserParseMultiplicativeExpression
(struct Parser *parser);

struct Ast*
ParserParsePushStatement
(struct Parser *parser);

struct Ast*
ParserParsePrintStatement
(struct Parser *parser);

#endif
