#include "mtoken.h"

struct mtoken *mtoken_new(void) {
    struct mtoken *token = malloc(sizeof(struct mtoken));
    token->type = T_NONE;
    token->lexeme = NULL;
    token->value = 0.0f;
    return token;
}

int mtoken_free(struct mtoken* token) {
    free(token);
    return 0;
}

struct mtoken *mtoken_init(enum TOKEN type, char* lexeme, float value) {
    struct mtoken *token = mtoken_new();
    token->type = type;
    token->lexeme = lexeme;
    token->value = value;
    return token;
}

void print_token(struct mtoken* tok) {
    if (!tok) return;

    switch (tok->type) {
        case T_NONE:
            printf("NONE\n");
            break;
        
        case T_EOF:
            printf("EOF\n");
            break;

        case T_NUMBER:
            printf("NUMBER: %f\n", tok->value);
            break;

        case T_IDENTIFIER:
            printf("IDENT: %s\n", tok->lexeme);
            break;

        case T_PLUS:
            printf("PLUS\n");
            break;
        
        case T_MINUS:
            printf("MINUS\n");
            break;
        
        case T_TIMES:
            printf("TIMES\n");
            break;
        
        case T_DIV:
            printf("DIV\n");
            break;
        
        case T_LPAREN:
            printf("LPAREN\n");
            break;
        
        case T_RPAREN:
            printf("RPAREN\n");
            break;

        default:
            printf("TOKEN %d\n", tok->type);
    }
}

struct mtoken *get_1_char(char c) {
    if (c == '+') return mtoken_init(T_PLUS, "+", 0.0f);
    if (c == '-') return mtoken_init(T_MINUS, "-", 0.0f);
    if (c == '*') return mtoken_init(T_TIMES, "*", 0.0f);
    if (c == '/') return mtoken_init(T_DIV, "/", 0.0f);
    if (c == '(') return mtoken_init(T_LPAREN, "(", 0.0f);
    if (c == ')') return mtoken_init(T_RPAREN, ")", 0.0f);
    if (c == '=') return mtoken_init(T_ASSIGN, "=", 0.0f);
    if (c == '<') return mtoken_init(T_LT, "<", 0.0f);
    if (c == '>') return mtoken_init(T_GT, ">", 0.0f);
    if (c == ',') return mtoken_init(T_COMMA, ",", 0.0f);
    if (c == '.') return mtoken_init(T_DOT, ".", 0.0f);
    if (c == ':') return mtoken_init(T_COLON, ":", 0.0f);
    if (c == '{') return mtoken_init(T_LBRACE, "{", 0.0f);
    if (c == '}') return mtoken_init(T_RBRACE, "}", 0.0f);
    if (c == '[') return mtoken_init(T_LBRACKET, "[", 0.0f);
    if (c == ']') return mtoken_init(T_RBRACKET, "]", 0.0f);
    if (c == '%') return mtoken_init(T_MOD, "percent", 0.0f);
    return NULL;
}

struct mtoken *get_2_char(char c1, char c2) {
    switch (c1) {
        case '<': {
            if (c2 == '=') return mtoken_init(T_LTE, "<=", 0.0f);
            return mtoken_init(T_LT, "<", 0.0f);
        }

        case '>': {
            if (c2 == '=') return mtoken_init(T_GTE, ">=", 0.0f);
            return mtoken_init(T_GT, ">", 0.0f);
        }

        case '=': {
            if (c2 == '=') return mtoken_init(T_EQ, "==", 0.0f);
            return mtoken_init(T_ASSIGN, "=", 0.0f);
        }

        case '!': {
            if (c2 == '=') return mtoken_init(T_NEQ, "!=", 0.0f);
            return NULL;
        }

        default:
            return get_1_char(c1);
    }
}   