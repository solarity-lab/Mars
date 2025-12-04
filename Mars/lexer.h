#ifndef LEXER_H
#define LEXER_H

#include "mars.h"
#include "token.h"

#define WHITE_SPACE ' '
#define NEW_LINE '\n'
#define END_CHAR '\0'

struct Lexer {
    char cur;
    int index;

    int line;
    int row;

    char* source;
    int size;
};

#define LEXER_NEXT_CHAR(lexer) (lexer->cur = lexer->source[lexer->index++])
#define LEXER_IS_WHITE_SPACE(lexer) ((lexer)->cur == ' ' || (lexer)->cur == '\t' || (lexer)->cur == '\n')

struct Lexer *LexerNew(void);

struct Lexer *LexerNewSource(char* source);

char LexerNextChar(struct Lexer* lexer);

struct Token *LexerNextToken(struct Lexer* lexer);

int LexerSkipWhiteSpace(struct Lexer* lexer);

struct Token *LexerTokenizeSyntax(struct Lexer *lexer);
struct Token *LexerTokenizeNumber(struct Lexer *lexer);
struct Token *LexerTokenizeKeyWord(struct Lexer *lexer);

#endif
