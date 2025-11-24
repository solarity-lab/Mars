#include "parser.h"

// fujiko
// ryuda-kosei

struct Parser*
ParserNew(void) {
    struct Parser *parser = (struct Parser*) malloc(sizeof(struct Parser));

    parser->token = NULL;
    parser->next = NULL;
    parser->lexer = NULL;

    return parser;
}

struct Ast*
ParserParse
(struct Parser *parser) {
    if (parser->token->token == PUSH) return ParserParsePushStatement(parser);
    if (parser->token->token == PRINT) return ParserParsePrintStatement(parser);
    return ParserParseAdditiveExpression(parser);
}

struct Ast*
ParserParseProgram
(struct Parser *parser) {
    struct Ast *program = AstNew();
    
    program->type = AST_PROGRAM;

    parser->token = LexerNextToken(parser->lexer);

    while (parser->token->token != NONE) {
        struct Ast *children = ParserParse(parser);

        AstAddChildren(program, children);
    }

    return program;
}

struct Ast*
ParserParsePrimaryExpression
(struct Parser *parser) {
    if (parser->token->token == NUMBER) return AstSetParent(AST_LITERAL, parser->token->value, NULL);
    if (parser->token->token == NAME) return AstSetParent(AST_IDENTIFER, 0, parser->token->lexeme);
    return AstSetParent(AST_NONE, 0, NULL);
}

struct Ast*
ParserParseAdditiveExpression
(struct Parser *parser) {
    struct Ast *left = ParserParseMultiplicativeExpression(parser);

    while (parser->token->token == PLUS || parser->token->token == MINUS) {
        enum TOKEN_TYPE op = parser->token->token;
        parser->token = LexerNextToken(parser->lexer);

        struct Ast *right = ParserParseMultiplicativeExpression(parser);
        left = AstMakeBinaryExpression(left, right, op);
    }

    return left;
}

struct Ast*
ParserParseMultiplicativeExpression
(struct Parser *parser) {
    struct Ast *left = ParserParsePrimaryExpression(parser);
    parser->token = LexerNextToken(parser->lexer);

    while (parser->token->token == DIV || parser->token->token == MUL) {
        enum TOKEN_TYPE op = parser->token->token;
        parser->token = LexerNextToken(parser->lexer);

        struct Ast *right = ParserParsePrimaryExpression(parser);
        left = AstMakeBinaryExpression(left, right, op); 

        parser->token = LexerNextToken(parser->lexer);
    }

    return left;
}

struct Ast*
ParserParsePushStatement    
(struct Parser *parser) {
    struct Ast *ast = AstSetParent(AST_PUSH, 0, NULL);

    parser->token = LexerNextToken(parser->lexer);
    ast->expression = ParserParseAdditiveExpression(parser);

    return ast;
}

struct Ast*
ParserParsePrintStatement
(struct Parser *parser) {
    struct Ast *ast = AstSetParent(AST_PRINT, 0, NULL);

    parser->token = LexerNextToken(parser->lexer);
    ast->expression = ParserParseAdditiveExpression(parser);

    return ast;
}
