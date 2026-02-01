#ifndef MPROTO_H
#define MPROTO_H

/* Phần I) định nghĩa ProtoFormat 

*   ProtoFormat là gì?
    - ProtoFormat là khung sườn để VM (máy ảo) xử lý mã máy, quản lý stack, tạo hằng số, lưu trữ biến, đếm mã máy, quản lý bộ nhớ,...
    - Có thể dùng cho hàm, hàm lồng nhau (closure)
*/

#include "mobj.h"   /*  cho bảng hằng số, stack, global, ... */
#include "mars.h"   /* dùng cho mã máy */
#include "mgc.h"    /* Garbage Collector */
#include "mlabel.h" /* label */
#include "mgrid.h"  /* grid */

enum ObjectType;
struct ProgramLabel;

struct ProtoFormat {
    struct Object** para;                   /* tham số (parameter) dùng cho hàm */
    MarsSize para_size;                     /* kích thước bộ tham số */

    Instruction* code;                      /* mã máy thô */

    struct Object** s;                      /* ngăn xếp */
    struct Object** k;                      /* bẳng hằng, là nơi lưu trữ dự liệu có sẵn, tối ưu khi tạo value */
    struct Object** g;                      /* bảng toàn cục, mọi proto đều trỏ chung vô bảng toàn cục chung này */
    struct Object** l;                      /* bảng cục bộ */

    MarsSize s_size;                        /* kích thước ngăn xếp */
    MarsSize k_size;                        /* kích thước bẳng hằng số */
    MarsSize g_size;                        /* kích thước bảng toàn cục */
    MarsSize l_size;                        /* kích thước bẳng cục bộ */

    MarsSize s_capacity;
    MarsSize k_capacity;
    MarsSize g_capacity;
    MarsSize l_capacity;

    MarsSize c_size;                        /* kích thước mã máy (instruction) */

    struct ProtoFormat* prev;               /* ProtoFormat trước dùng cho tra các ProtoFormat lồng nhau */

    int pc;                                 /* bộ đếm bytecode (program counter) */

    struct ProgramLabel labels;

    struct Grid* grid;

    struct GarbageCollector* gc;
};

/*
    Phần II) Xử lý ProtoFormat
*/

#define nextc(p) ((p)->code[(p)->pc++])         /* lấy opcode tiếp theo trong instruction */

#define curc(p) ((p)->code[(p)->pc])            /* lấy opcode hiện tại */

#define prevc(p) ((p)->pc--)                    /* giảm pc, cho backward opcode */

#define jump(p, offset) ((p)->pc = (offset))    /* nhảy đến thứ tự cố định */

struct ProtoFormat *ProtoNew(void);             /* hey why dont write commnet abiut me? */

/*
    Khởi tạo ProtoFormat bao gồm:
        - khởi tạo global, local, stack, bảng hằng
        - khởi tạo bộ thu gom rác (garbage collector)
*/
struct ProtoFormat *ProtoInit(struct ProtoFormat* proto);


/*
    Hàm đẩy object lên stack, nếu không có lỗi thì trả về FTRUE
*/
Flag ProtoStackPush(struct ProtoFormat* proto, struct Object* value);

/*
    Hàm pop object ra khỏi stack, nếu không có lỗi thì trả về FTRUE 
*/
Flag ProtoStackPop(struct ProtoFormat* proto);

/*
    Xem Object hiện tại của stack
*/
struct Object *ProtoStackBack(struct ProtoFormat* proto);

/*
    Hàm pop object ra khỏi stack, trả về nó
    hàm này không free, chỉ giảm refcount
    người dùng phải tự quản lý bộ nhớ qua hàm GCmove
*/
struct Object* ProtoStackTake(struct ProtoFormat* proto);

/*
    Thao tác biến toàn cục bao gồm load và store
*/
struct Object* ProtoLoadGlobal(struct ProtoFormat *proto, address_t address);
struct Object* ProtoStoreGlobal(struct ProtoFormat *proto, address_t address, struct Object* value, enum ObjectType type);


/*
    Thao tác biến cục bộ bao gồm load và store
*/
struct Object* ProtoLoadLocal(struct ProtoFormat *proto, address_t address);
struct Object* ProtoStoreLocal(struct ProtoFormat *proto, address_t address, struct Object* value, enum ObjectType type);

/*
    Các hàm hỗ trợ khác
*/

int ProtoPushNum(struct ProtoFormat* proto, Number_t number);

#endif /* MPROTO_H */