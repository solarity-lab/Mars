#include "mlexer.h"
#include "mtool.h"

struct mlexer *mlexer_new(char *buf, int len, char *file) {
    struct mlexer *lexer = malloc(sizeof(struct mlexer));
    lexer->buf = buf;
    lexer->len = len;
    lexer->pos = 0;
    lexer->cur = buf[0];
    lexer->file = file;
    lexer->line = 1;
    lexer->row = 1;
    return lexer;
}

int mlexer_free(struct mlexer* lexer) {
    free(lexer);
    return 0;
}

int skipwhitespace(struct mlexer* lexer) {
    while (peekchar(lexer, 0) == ' ' || peekchar(lexer, 0) == '\t' || peekchar(lexer, 0) == '\n' || peekchar(lexer, 0) == '\r') {
        advance(lexer, 1);
    }
    return 0;
}

int advance(struct mlexer* lexer, int n) {
    if (lexer->pos + n > lexer->len) {
        return -1;
    }

    if (peekchar(lexer, 0) == '\n') {
        lexer->line++;
        lexer->row = 1;
    } else {
        lexer->row += n;
    }

    lexer->pos += n;
    return 0;
}

char nextchar(struct mlexer* lexer) {
    if (lexer->pos >= lexer->len) {
        return '\0';
    }

    lexer->cur = lexer->buf[lexer->pos];
    if (lexer->cur == '\n') {
        lexer->line++;
        lexer->row = 1;
    } else {
        lexer->row++;
    }

    ++lexer->pos;

    return lexer->cur;
}

char peekchar(struct mlexer* lexer, int n) {
    if (lexer->pos + n > lexer->len) {
        return '\0';
    }
    return lexer->buf[lexer->pos + n];
}   

char prevchar(struct mlexer* lexer) {
    if (lexer->pos == 0) return '\0';
    lexer->pos--;
    lexer->cur = lexer->buf[lexer->pos];
    return lexer->cur;
}

struct mtoken* nexttoken(struct mlexer* lexer) {
    skipwhitespace(lexer);

    char c = nextchar(lexer);

    if (c == '\0') {
        return mtoken_init(T_EOF, "EOF", 0.0f);
    }

    if (ischardigit(c)) {
        return tokenize_number(lexer);
    }

    if (ischaridentifier(c)) {
        return tokenize_identifier(lexer);
    }

    if (ischarsymbol(c)) {
        return tokenize_symbol(lexer);
    }

    return mtoken_init(T_NONE, "NULL", 0.0f);
}

struct mtoken* tokenize_number(struct mlexer* lexer) {
    int start = lexer->pos - 1;

    while (ischardigit(peekchar(lexer, 0))) {
        nextchar(lexer);
    }

    int len = lexer->pos - start;
    char* num = Mstrndup(lexer->buf + start, len);

    return mtoken_init(T_NUMBER, num, atof(num));
}

struct mtoken* tokenize_identifier(struct mlexer* lexer) {
    int start = lexer->pos - 1;

    while (ischaridentifier(peekchar(lexer, 0))) {
        nextchar(lexer);
    }

    int len = lexer->pos - start;
    char* id = Mstrndup(lexer->buf + start, len);

    return mtoken_init(keyword_lookup(id), id, 0);
}

struct mtoken* tokenize_symbol(struct  mlexer* lexer) {
    char c = lexer->cur;
    char c2 = peekchar(lexer, 0);
    
    if (ischarsymboldouble(c, c2)) {
        nextchar(lexer);
        struct mtoken* tok = get_2_char(c, c2);
        if (!tok) {
            error_at("Unknown symbol", lexer->file, lexer->line, lexer->row);
        }
        return tok;
    }

    struct mtoken* tok = get_1_char(c);
    if (!tok) {
        error_at("Unknown symbol", lexer->file, lexer->line, lexer->row);
    }

    return tok;
}

struct mtoken* lookahead(struct mlexer* lexer) {
    struct mlexer backup = *lexer;
    struct mtoken* tok = nexttoken(lexer);
    *lexer = backup;
    return tok;
}
