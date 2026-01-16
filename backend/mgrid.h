#ifndef MGRID_H
#define MGRID_H

#include "mobj.h"
#include "mgc.h"

#define MAX_GRID_STACK 500

#define _RES1_SIZE 500
#define _RES2_SIZE 500
#define _RES3_SIZE 500

enum RES_T {
    RES1,
    RES2,
    RES3
};

struct Pointer {
    int _p;
    enum RES_T _res;
};

struct Res {
    struct Object** data;
    int size;
};

struct Grid {
    struct Pointer p;

    struct Res *res1;
    struct Res *res2;
    struct Res *res3;

    struct GarbageCollector* gc;
};

int GridFree(struct Grid* grid);
int ResFree(struct Res* res);

struct Res* ResNew(int size);

struct Res* GridGetRes(struct Grid* grid, enum RES_T _res);

/*
    Khởi tạo grid với kích thước GridStack
    Khi khởi tạo con trỏ luôn ở ô số 0 và trỏ tới stack res1
*/

struct Grid* GridCreate(int _res1_size, int _res2_size, int _res3_size);

/*
    Hàm di chuyển con trỏ chuột
*/

struct Grid* GridMoveTo(struct Grid* grid, int _p, enum RES_T _res);

/*
    Hàm ghi giá trị vô grid
*/

struct Grid* GridWrite(struct Grid* grid, struct Object* value);

/*
    Hàm đọc dự liệu hiện tại con trỏ đang trỏ tới
*/

struct Object* GridRead(struct Grid* grid);

/*
    Hàm xóa dự liệu hiện tại con trỏ đang trỏ tối
*/

struct Grid* GridErase(struct Grid* grid);

#endif // MGRID_H