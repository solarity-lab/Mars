#ifndef OPCODE_H
#define OPCODE_H

#define OKADD                       0x01
#define OKSUB                       0x02
#define OKMUL                       0x03
#define OKDIV                       0x04
#define OKMOD                       0x05
#define OKNEG                       0x06

#define OKPUSH_FLOAT                0x10
#define OKPUSH_BOOL                 0x11
#define OKPOP                       0x12
#define OKPRINT                     0x13

#define OKLOAD                      0x20
#define OKSTORE                     0x21
#define OKADDRESS                   0x22

#define OKLOAD_LOCAL                0x23
#define OKSTORE_LOCAL               0x24

#define OKEQ                        0x30
#define OKNEQ                       0x31
#define OKLT                        0x32
#define OKLTE                       0x33
#define OKGT                        0x34
#define OKGTE                       0x35

#define OKAND                       0x36
#define OKOR                        0x37
#define OKNOT                       0x38

#define OKJMP                       0x40
#define OKJMP_IF_FALSE              0x41
#define OKCALL                      0x42
#define OKRETURN                    0x43
#define OKHALT                      0x44

#define OKMAKE_ARGS                 0x50
#define OKMAKEFUNC                  0x51
#define OKSTART_FUNC                0x52
#define OKEND_FUNC                  0x53

#define OKMAKE_CLOSURE              0x54
#define OKLOAD_CLOSURE              0x55
#define OKSTORE_CLOSURE             0x56
#define OKEND_CLOSURE               0x57

#define CCMOVE_TO                   0x60
#define CCWRITE                     0x61
#define CCERASE                     0x62
#define CCCREATE                    0x63
#define CCREAD                      0x64
#define CCCLOSE                     0x65

#endif /* OPCODE_H */
