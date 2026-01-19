#include <stdio.h>
#include <string.h>

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
    int dump_mcode = 0;
    char* file = NULL;

    if (argc == 2) {
        file = argv[1];
    } else if (argc == 3 && strcmp(argv[1], "-m") == 0) {
        dump_mcode = 1;
        file = argv[2];
    } else {
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "  %s <source-file>\n", argv[0]);
        fprintf(stderr, "  %s -m <source-file>   (dump bytecode)\n", argv[0]);
        return 1;
    }

    struct mbuff* zio = mbuff_read_file(file);
    if (!zio) {
        fprintf(stderr, "Cannot read file: %s\n", file);
        return 1;
    }

    struct mlexer* lexer = mlexer_new(zio->buffer, zio->size, file);
    struct mparser* parser = mparser_new(lexer);
    struct mast* ast = mparser_parse(parser);

    struct menvi* envi = menvi_new();
    struct mcompiler* compiler = mcompiler_new();
    struct mcode* code = mcompiler_compile_ast_program(ast, compiler, envi);

    if (dump_mcode) {
        mcode_print(code);
        return 0;
    }

    struct ProtoFormat* proto = ProtoNew();
    ProtoInit(proto);

    ProtoRunCode(proto, code->bytecode, code->size);

    return 0;
}
