#include "mgrid.h"

int GridFree(struct Grid* grid) {
    ResFree(grid->res1);
    ResFree(grid->res2);
    ResFree(grid->res3);
    free(grid);
    return 0;
}

int ResFree(struct Res* res) {
    free(res->data);
    free(res);
    return 0;
}

struct Res* GridGetRes(struct Grid* grid, enum RES_T _res) {
    switch (_res) {
        case RES1:
            return grid->res1;
        case RES2:
            return grid->res2;
        case RES3:
            return grid->res3;
    }    

    return NULL;
}

struct Res* ResNew(int size) {
    struct Res* data = malloc(sizeof(struct Res));
    data->data = malloc(sizeof(struct Object*) * size);

    memset(data->data, 0, sizeof(struct Object*) * size);
    
    data->size = size;
    return data;
}

struct Grid* GridCreate(int _res1_size, int _res2_size, int _res3_size) {
    struct Grid* grid = malloc(sizeof(struct Grid));
    
    grid->p._p = 0;
    grid->p._res = RES1;

    grid->res1 = ResNew(_res1_size);
    grid->res2 = ResNew(_res2_size);
    grid->res3 = ResNew(_res3_size);
    
    return grid;
}

struct Grid* GridMoveTo(struct Grid* grid, int _p, enum RES_T _res) {
    struct Res* res = GridGetRes(grid, _res);

    if (_p >= res->size) {
        return grid;
    }

    grid->p._p = _p;
    grid->p._res = _res;

    return grid;
}

struct Grid* GridWrite(struct Grid* grid, struct Object* value) {
    struct Res* res = GridGetRes(grid, grid->p._res);

    struct Object* old = res->data[grid->p._p];

    if (old) {
        DECR_REF(old);
        GCmove(grid->gc, old);
    }

    res->data[grid->p._p] = value;

    INCR_REF(value);

    return grid;
}

struct Object* GridRead(struct Grid* grid) {
    struct Res* res = GridGetRes(grid, grid->p._res);
    return res->data[grid->p._p];
}

struct Grid* GridErase(struct Grid* grid) {
    struct Res* res = GridGetRes(grid, grid->p._res);
    struct Object* old = res->data[grid->p._p];
        
    if (!old) {
        return grid;
    }

    res->data[grid->p._p] = NULL;

    DECR_REF(old);
    GCmove(grid->gc, old);

    return grid;
}