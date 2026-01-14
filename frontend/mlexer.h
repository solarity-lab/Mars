#ifndef MLEXER_H
#define MLEXER_H

#include "mtoken.h"
#include "mdebug.h"
#include "msyntax.h"
#include <stdlib.h>
#include <string.h>

struct mlexer {
    char *buf;
    int len;
    int pos;

    char cur;

    int line;
    int row;

    char* file;
};

struct mlexer *mlexer_new(char *buf, int len, char *file);
int mlexer_free(struct mlexer* lexer);

char nextchar(struct mlexer* lexer);
char peekchar(struct mlexer* lexer, int n);
char prevchar(struct mlexer* lexer);

int skipwhitespace(struct mlexer* lexer);

int advance(struct mlexer* lexer, int n);

struct mtoken* nexttoken(struct mlexer* lexer);
struct mtoken* lookahead(struct mlexer* lexer);

struct mtoken* tokenize_number(struct mlexer* lexer);
struct mtoken* tokenize_identifier(struct mlexer* lexer);
struct mtoken* tokenize_symbol(struct  mlexer* lexer);

#endif // MLEXER_H
