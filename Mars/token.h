#ifndef TOKEN_H
#define TOKEN_H

#include "mars.h"

#define TOKEN(t, l, v) TokenInit(t, l, v)
#define IS_IDENTIFIER(a) ((a) >= 'a' && (a) <= 'z' || (a) >= 'A' && (a) <= 'Z' || (a) == '_')
#define IS_NUMBER(a) ((a) >= '0' && (a) <= '9' || (a) == '.')
#define NULL_TOKEN TOKEN(NONE, NULL, 0)
#define IS_KEYWORD(a) ((a) == '+' \ 
                    || (a) == '-' \
                    || (a) == '*' \
                    || (a) == '/' \
                    || (a) == ':' \
                    || (a) == '=' \
                    || (a) == ',' \
                    || (a) == '(' \
                    || (a) == ')' \
                    || (a) == '{' \
                    || (a) == '}' \
                    || (a) == '[' \
                    || (a) == ']' \
                    || (a) == '{' \
                    || (a) == '}')

enum TOKEN_TYPE {
    CREAT, 
    PUSH, 
    POP, 
    PRINT, 
    DEL, 
    NONE, 
    NAME, 
    NUMBER, 
    PLUS, 
    MINUS, 
    DIV, 
    MUL, 
    SET, 
    LPAREN, 
    RPAREN, 
    LBRACE, 
    RBRACE, 
    LBRACKET, 
    RBRACKET, 
    COMMA, 
    ASSIGN, 
    COLON
};

struct Token {
    enum TOKEN_TYPE token;
    char* lexeme;
    int value;
};

struct Token *TokenNew(void);
struct Token *TokenInit(enum TOKEN_TYPE token, char* lexeme, int value);
struct Token *GetIdentifier(char* iden);
struct Token *TokenGet1Char(char c);

#endif
