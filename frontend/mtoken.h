#ifndef STOKEN_H
#define STOKEN_H

#include <stdlib.h>
#include <stdio.h>

#define ischardigit(c) ((c >= '0' && c <= '9') || c == '.')
#define ischaridentifier(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
#define ischarsymbol(c) (c == '+' \
                        || c == '-' \
                        || c == '*' \
                        || c == '/' \
                        || c == '(' \
                        || c == ')' \
                        || c == ',' \
                        || c == '.' \
                        || c == ':' \
                        || c == '!' \
                        || c == '<' \
                        || c == '>' \
                        || c == '%' \
                        || c == '[' \
                        || c == ']' \
                        || c == '{' \
                        || c == '}' \
                        || c == '=')

#define ischarsymboldouble(c1, c2) ((c1 == '<' && c2 == '=') || (c1 == '>' && c2 == '=') || (c1 == '!' && c2 == '=') || (c1 == '=' && c2 == '='))

enum TOKEN {
    T_NONE,
    T_PLUS,
    T_MINUS,
    T_TIMES,
    T_DIV,
    T_MOD,

    T_LPAREN,
    T_RPAREN,

    T_IDENTIFIER,
    T_NUMBER,
    
    T_ASSIGN,

    T_COMMA,
    T_DOT,
    T_COLON,

    T_LBRACE,
    T_RBRACE,
    T_LBRACKET,
    T_RBRACKET,
    
    T_EQ,
    T_NEQ,
    T_LT,
    T_LTE,
    T_GT,
    T_GTE,

    T_AND,
    T_OR,
    T_NOT,
    T_TRUE,
    T_FALSE,

    T_FUNC,
    T_LET,
    T_RETURN,
    T_IF,
    T_ELSE,
    T_THEN,
    T_FOR,
    T_IN,
    T_BREAK,
    T_CONTINUE,
    T_WHILE,
    T_LOOP,
    T_DO,
    T_END,

    T_PRINT,
    T_SCAN,

    T_MOVE,
    T_TO,
    T_WRITE,
    T_REWRITE,
    T_READ,
    T_CREATE,
    T_CLOSE,
    T_ERASE,

    T_EOF,
};

#define TOK_INFO \
    int line;    \
    int row;     \
    int index;

struct mtoken {
    TOK_INFO;

    enum TOKEN type;
    char *lexeme;
    float value;
};

struct mtoken *mtoken_new(void);
struct mtoken *mtoken_init(enum TOKEN type, char* lexeme, float value);
int mtoken_free(struct mtoken* token);
void print_token(struct mtoken* tok);

struct mtoken *get_1_char(char c);
struct mtoken *get_2_char(char c1, char c2);

#endif // STOKEN_H
