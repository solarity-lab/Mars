#ifndef MOBJ_H
#define MOBJ_H

#include <stdlib.h>
#include <stdio.h>

/*
    File này định nghĩa kiểu object, là object chung cho toàn bộ mars
    object dùng để tính toán, push, pop, stack,...
*/

#include "mars.h"

// định nghĩa null object
#define null_obj ObjectNew()

enum ObjectType {
    O_NUMBER, // kiểu số (bao gồm float, int)
    O_BOOL, // kiểu bool (true, false)
    O_STRING, // kiểu chuỗi (ascii, unicode, utf-8, utf-16, utf-32)
    O_ARRAY, // mảng [obj1, obj2, ...]
    O_PROTO, // Proto dùng cho hàm, hoặc thread
    O_CLOSURE, // closure, kiểu đặc biệt dành cho hàm
    O_NULL, // kiểu mặc định NULL

    O_GLOBAL,
    O_LOCAL,
};

struct Object {
    int ref_count;              // số lượng tham chiếu dùng cho GC

    address_t address;          // địa chỉ ảo, dùng cho biến

    enum ObjectType type;       // kiểu dữ liệu của object
    Number_t value;            // giá trị chính của object

    struct Object* f_value; // giá trị của biến, biến sẽ có dự liệu tham chiếu đến field này

    Flag is_closure;         // tag closure
    Flag is_return;          // tag có phải return object hay không
};

/*
    sữa phải đi với oreo
    struct phải đi với new
    còn anh thì không đến được với em... 
        -Quân tử vib- à nhầm coder
*/
struct Object* ObjectNew(void);

struct Object* ObjectMakeNumber(Number_t number);
struct Object* ObjectMakeBool(int _b);

// hàm giải phóng
int ObjectFree(struct Object* object);

#endif // MOBJ_H