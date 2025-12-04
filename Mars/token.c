#include "token.h"

struct Token *TokenNew(void) {
    struct Token *token = (struct Token*) malloc(sizeof(struct Token));
    token->token = NONE;
    token->lexeme = NULL;
    token->value = 0;

    return token;
}

struct Token *TokenInit(enum TOKEN_TYPE token, char* lexeme, int value) {
    struct Token *tok = TokenNew();

    tok->token = token;
    tok->lexeme = lexeme;
    tok->value = value;

    return tok;
}

struct Token *GetIdentifier(char* iden) {
    if (strcmp(iden, "PUSH") == 0) return TOKEN(PUSH, NULL, 0);
    if (strcmp(iden, "CREAT") == 0) return TOKEN(CREAT, NULL, 0);
    if (strcmp(iden, "POP") == 0) return TOKEN(POP, NULL, 0);
    if (strcmp(iden, "PRINT") == 0) return TOKEN(PRINT, NULL, 0);
    if (strcmp(iden, "DEL") == 0) return TOKEN(DEL, NULL, 0);
    if (strcmp(iden, "SET") == 0) return TOKEN(SET, NULL, 0);

    return TOKEN(NAME, strdup(iden), 0);
}

struct Token *TokenGet1Char(char c) {
    if (c == '+') return TOKEN(PLUS, NULL, 0);
    if (c == '-') return TOKEN(MINUS, NULL, 0);
    if (c == '/') return TOKEN(DIV, NULL, 0);
    if (c == '*') return TOKEN(MUL, NULL, 0);
    if (c == '(') return TOKEN(LPAREN, NULL, 0);
    if (c == ')') return TOKEN(RPAREN, NULL, 0);
    if (c == '{') return TOKEN(LBRACE, NULL, 0);
    if (c == '}') return TOKEN(RBRACE, NULL, 0);
    if (c == '[') return TOKEN(LBRACKET, NULL, 0);
    if (c == ']') return TOKEN(RBRACKET, NULL, 0);
    if (c == ',') return TOKEN(COMMA, NULL, 0);
    if (c == '=') return TOKEN(ASSIGN, NULL, 0);
    if (c == ':') return TOKEN(COLON, NULL, 0);

    return NULL_TOKEN;
}
