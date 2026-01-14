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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    struct ProtoFormat* proto = ProtoNew();
    ProtoInit(proto);

    while (1) {
        ProtoStoreGlobal(proto, 0, ObjectNew(), O_NUMBER);
        
        GCStartClean(proto->gc);
    }

    return 0;
}
