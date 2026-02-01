#ifndef MGRID_H
#define MGRID_H

#include "mobj.h"
#include "mgc.h"
#include "mproto.h"
#include "mars.h"

struct ProtoFormat;

struct Cursor {
    MarsSize row, column;
};

struct Grid {
    MarsSize width, height;

    struct Cursor *cursor;

    struct Object** data;

    struct Object* current;
};

struct Cursor* CursorNew(void);

struct Cursor* CursorMoveTo(struct Cursor* cursor, MarsSize row, MarsSize column);

struct Grid* GridCreate(MarsSize width, MarsSize height);

struct Grid* GridMoveTo(struct Grid* grid, MarsSize row, MarsSize column);

struct Grid* ProtoGridWrite(struct ProtoFormat *proto, struct Object* value);

struct Grid* ProtoGridErase(struct ProtoFormat *proto);

void GridPrint(struct Grid* grid);

int ProtoGridFree(struct ProtoFormat* proto, struct Grid* grid);

#endif // MGRID_H