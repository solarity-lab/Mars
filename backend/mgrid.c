#include "mgrid.h"

struct Cursor* CursorNew(void) {
    struct Cursor* cursor = malloc(sizeof(struct Cursor));
    cursor->row = 0;
    cursor->column = 0;

    return cursor;
}

struct Cursor* CursorMoveTo(struct Cursor* cursor, MarsSize row, MarsSize column) {
    cursor->row = row;
    cursor->column = column;
    return cursor;
}

struct Grid* GridCreate(MarsSize width, MarsSize height) {
    struct Grid* grid = malloc(sizeof(struct Grid));

    grid->cursor = CursorNew();

    grid->width = width;
    grid->height = height;

    grid->data = malloc(width * height * sizeof(struct Object*));

    memset(grid->data, 0, width * height * sizeof(struct Object*));

    grid->current = NULL;

    return grid;
}

/*
    Grid (width = 5, height = 2)

    Row 0: [1, 2, 3, 4, 5]
    Row 1: [6, 7, 8, 9, 10]

    move to (row = 1, column = 2) hàng 2, cột 2

    Row 1: [6, 7, (8), 9, 10]

    muốn xuống 1 dòng thì phải đếm từ phẩn tử grid[0] đến grid[width]
    nếu muốn xuống nữa thì phải đếm từ phần tử grid[0 + width] đến grid[width + width]

    như vật muốn xuống n dòng thì phải đếm từ phần tử grid[0] đến grid[width * n]
    cộng thêm cột muốn đi nữa thì công thức là:

    [index = row * width + column] 
    
    với:

    (row * width):        xuống row dòng
    (+ column):           dịch sang bên phải column cột
*/

struct Grid* GridMoveTo(struct Grid* grid, MarsSize row, MarsSize column) {
    if (row >= grid->height || column >= grid->width)
        return NULL;

    CursorMoveTo(grid->cursor, row, column);

    grid->current = grid->data[row * grid->width + column];
    return grid;
}

struct Grid* ProtoGridWrite(struct ProtoFormat *proto, struct Object* value) {
    struct Grid* grid = proto->grid;

    struct Object* old = grid->current;

    if (old) {
        DECR_REF(old);
        GCmove(proto->gc, old);
    }

    INCR_REF(value);
    grid->current = value;

    grid->data[grid->cursor->row * grid->width + grid->cursor->column] = value;

    return grid;
}

struct Grid* ProtoGridErase(struct ProtoFormat *proto) {
    struct Grid* grid = proto->grid;

    struct Object* old = grid->current;

    if (old) {
        DECR_REF(old);
        GCmove(proto->gc, old);
    }

    grid->current = NULL;
    grid->data[grid->cursor->row * grid->width + grid->cursor->column] = NULL;
    return grid;
}
void GridPrint(struct Grid* grid) {
    int w = grid->width;
    int h = grid->height;

    printf("    ");
    for (int c = 0; c < w; c++)
        printf("+--------");
    printf("+\n");

    for (int r = 0; r < h; r++) {
        printf("%-3d ", r);

        for (int c = 0; c < w; c++) {
            struct Object* value = grid->data[r * w + c];
            if (value)
                printf("| %6.2f ", value->value);
            else
                printf("| %6s ", "Null");
        }
        printf("|\n");

        printf("    ");
        for (int c = 0; c < w; c++)
            printf("+--------");
        printf("+\n");
    }
}

int GridFree(struct Grid* grid) {
    free(grid->data);
    free(grid->cursor);
    free(grid);
    return 0;
}