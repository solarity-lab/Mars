#include "./frontend/menvi.h"
#include "./frontend/mcompiler.h"
#include "./frontend/mcode.h"
#include "./frontend/mparser.h"
#include "./frontend/mlexer.h"  
#include "./frontend/mbuff.h"

#include "./backend/mproto.h"
#include "./backend/mars.h"
#include "./backend/mgc.h"
#include "./backend/mobj.h"
#include "./backend/meval.h"
#include "./backend/mvm.h"


int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source-file>\n", argv[0]);
        return 1;
    }

    char* file = argv[1];

    struct mbuff* zio = mbuff_read_file(file);
    struct mlexer* lexer = mlexer_new(zio->buffer, zio->size, file);
    struct mparser* parser = mparser_new(lexer);
    struct mast* ast = mparser_parse(parser);
    struct menvi* envi = menvi_new();
    struct mcompiler* compiler = mcompiler_new();
    struct mcode* code = mcompiler_compile_ast_program(ast, compiler, envi);

    struct ProtoFormat *proto = ProtoNew();
    ProtoInit(proto);

    ProtoRunCode(proto, code->bytecode, code->size);


    return 0;
}