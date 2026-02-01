#ifndef MARS_H
#define MARS_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

/* Mars Virtual Machine Definitions 
    - File này cung cấp những kiểu dữ liệu riêng cho mars, để có thể tương thích với mọi loại máy bao gồm: 64-bit, 32-bit, ...
    - File này cung cấp những thư viện cần thiết bao gồm thư viện C và các thư viện của Mars
    - File này định nghĩa API
*/

#if defined(UINT64_MAX) // nếu là máy 64-bit thì dùng uint64_t
    typedef uint64_t MarsSize;
    
    #define MARS_SIZE_BITS 64
    
#elif defined(UINT32_MAX) // nếu là máy 32-bit thì dùng uint32_t
    typedef uint32_t MarsSize;
    
    #define MARS_SIZE_BITS 32
#else               
    typedef unsigned int MarsSize; // còn lai dùng unsigned int
    
    #define MARS_SIZE_BITS 0       
#endif

/*
    Kieu du lieu so cho object
*/

typedef double Number_t;


/*
    Định nghĩa kiểu dữ liệu cơ bản
*/

typedef int             address_t;          // địa chỉ ảo cho Virtual Machine
typedef unsigned char   Instruction;        // Bytecode cho máy ảo

/*
    kiểu cờ 1 byte, dùng cho các field, flag chỉ có giá trị 0 hoặc 1
*/

typedef unsigned char    Flag;


/*
    FTRUE: Trả về 1 (true) như chuẩn C
    FFALSE: Trả về 0 (false) dùng cho malloc fail, ...
*/

#define FTRUE            1u         // 1 (true)
#define FFALSE           0u         // 0 (false)


/*
    Cung cấp các file cần thiết bao gồm thư viện C, thư viện Mars, ...
*/

#endif // MARS_H