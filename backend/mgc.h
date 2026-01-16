#ifndef MGC_H
#define MGC_H

#include <stdio.h>
#include <stdlib.h>

#include "mobj.h"

/*
    File này định nghĩa Garbage Collector nơi thu gom những object đã không còn ai tham chiếu
    Object không được free ngay mà đẩy lên garbage collector
    Garbage collector sẽ dọn theo chu kì
*/

#define GC_SAFE      0      // an toàn
#define GC_UNSAFE   -1      // không an toàn

#define GC_MAX 500          // số lớn nhất cho bộ rác, nếu bộ đếm rác lớn hơn cái này thì lập tức khởi động GC

#define INCR_REF(x) if ((x)) (x)->ref_count++
#define DECR_REF(x) if ((x)) (x)->ref_count--

struct GarbageCollector {
    /*
        Nơi chứa rác cho các object bị thu hồi bởi Garbage Collector
        các object trong bể sẽ bị giải phóng (free)
    */
    struct Object** pool;       // cho bọn vibecoder ko làm mà đòi có ăn (chắc ko có tôi đâu nhỉ)
    int p_size;                 // kích thước bể
    int p_capacity;

    int activated;              // flag được khởi động chưa
};


struct GarbageCollector* GCNew(void);

/*
    Hàm này đẩy các object lên garbage collector
    nếu các object này không còn tham chiếu (ref_count == 0), thì đẩy lên
    còn không thỉ trả về 0
*/
int GCmove(struct GarbageCollector* gc, struct Object* obj);

/*
    Giai đoạn khởi tạo bộ rác I (Init):
    bật nút activated cho garbage collector
    nếu không bật thì GC không dọn, tránh dùng GC một cách không quản lý, lung tung
*/
#define GCActivate(gc) ((gc)->activated = 1)

/*
    Giai đoạn Kiểm tra II (Check):
    Kiểm tra xem kích thước của garbage collector đã vượt mức tối đa có thể giải phóng chưa
    Nếu rồi thì sang giai đoạn tiếp theo
*/
int GCStartClean(struct GarbageCollector* gc);

/*
    Giai đoạn Quét III (Sweep):
    Duyệt toàn bộ danh sách bộ nhớ đã cấp phát, giải phóng (free)
    những Object không được đánh dấu ở bước Mark.
*/
int GCSweep(struct GarbageCollector* gc);

/*
    Giai đoạn tắt VI (End):
    tắt garbage collector, không còn hoạt động
*/
#define GCDeactivate(gc) ((gc)->activated = 0)

#endif // MGC_H