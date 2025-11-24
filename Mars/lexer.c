#include "lexer.h"

struct Lexer *LexerNew(void) {
    struct Lexer *lexer = malloc(sizeof(struct Lexer));
    lexer->cur = '\0';
   
    lexer->index = 0;
    lexer->line = 0;
    lexer->row = 0;
    lexer->size = 0;
    
    lexer->source = NULL;

    return lexer;
}

struct Lexer *LexerNewSource(char* source) {
    struct Lexer *lexer = LexerNew();
    lexer->source = source;
    lexer->size = strlen(source);
    if (lexer->size > 0) lexer->cur = source[0];
    else lexer->cur = '\0';    
    return lexer;
}

char LexerNextChar(struct Lexer* lexer) {
    lexer->index++;

    if (lexer->index >= lexer->size) {
        lexer->cur = '\0';
        return '\0';
    }

    lexer->cur = lexer->source[lexer->index];

    if (lexer->cur == '\n') {
        lexer->line++;
        lexer->row = 0;
    } else {
        lexer->row++;
    }

    return lexer->cur;
}


struct Token *LexerNextToken(struct Lexer* lexer) {
    for (;;) {
        LexerSkipWhiteSpace(lexer);

        char c = lexer->cur;

        if (c == '\0') return NULL_TOKEN;

        if (IS_IDENTIFIER(c)) return LexerTokenizeSyntax(lexer);
        if (IS_NUMBER(c)) return LexerTokenizeNumber(lexer);
        if (IS_KEYWORD(c)) return LexerTokenizeKeyWord(lexer);

        return NULL_TOKEN;
    }

    return NULL_TOKEN;
}


int LexerSkipWhiteSpace(struct Lexer* lexer) {
    while (LEXER_IS_WHITE_SPACE(lexer)) {
        LexerNextChar(lexer);
    }
    return 0;
}   

struct Token *LexerTokenizeSyntax(struct Lexer *lexer) {    
    char* buff = malloc(1024);
    int i = 0;

    while (IS_IDENTIFIER(lexer->cur)) {
        buff[i++] = lexer->cur;
        LexerNextChar(lexer);
    }

    buff[i] = '\0';

    struct Token *tok = GetIdentifier(buff);

    free(buff);
    return tok;
}

struct Token *LexerTokenizeNumber(struct Lexer *lexer) {
    int start = lexer->index;
    int length = 0;

    while (isdigit(lexer->cur)) {
        LexerNextChar(lexer);
        length++;
    }

    char* numstr = malloc(length + 1);
    memcpy(numstr, lexer->source + start, length);
    numstr[length] = '\0';

    float value = strtol(numstr, NULL, 10);

    struct Token* tok = TOKEN(NUMBER, numstr, value);

    return tok;
}

struct Token *LexerTokenizeKeyWord(struct Lexer *lexer) {
    char c = lexer->cur;
    LexerNextChar(lexer);
    return TokenGet1Char(c);
}
