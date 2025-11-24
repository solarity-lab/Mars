#include "parser.h"

int main() {
    char* source = "1 + 1 / 2";
    struct Lexer *lexer = LexerNewSource(source);
    struct Parser *parser = ParserNew();
    parser->lexer = lexer;
    struct Ast *ast = ParserParseProgram(parser);
    AstPrint(ast);
    return 0;
}
