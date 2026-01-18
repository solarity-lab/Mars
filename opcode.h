#ifndef OPCODE_H
#define OPCODE_H

#define OKADD '\x01'
#define OKSUB '\x02'
#define OKMUL '\x03'
#define OKDIV '\x04'

#define OKPUSH_NUM '\x05'
#define OKPUSH_BOOL '\x07'
#define OKPOP '\x36'
#define OKPRINT '\x08'

#define OKLOAD '\x09'
#define OKSTORE '\x10'
#define OKADDRESS '\x30'

#define OKEQ '\x11'
#define OKNEQ '\x12'
#define OKLT '\x13'
#define OKLTE '\x14'
#define OKGT '\x15'
#define OKGTE '\x16'

#define OKJMP '\x20'
#define OKJMP_IF_FALSE '\x21'

#define OKCALL '\x22'
#define OKRETURN '\x23'
#define OKMAKE_ARGS '\x31'
#define OKMAKEFUNC '\x32'
#define OKSTART_FUNC '\x38'
#define OKEND_FUNC '\x39'

#define OKMAKE_CLOSURE '\x33'
#define OKLOAD_CLOSURE '\x34'
#define OKSTORE_CLOSURE '\x35'
#define OKEND_CLOSURE '\x40'

#define OKHALT '\x37'

#define OKLOAD_LOCAL '\x24'
#define OKSTORE_LOCAL '\x25'

#define OKMOD '\x26'
#define OKNEG '\x27'
#define OKNOT '\x28'

// control
#define CCMOVE_TO '\x29'
#define CCWRITE '\x2a'
#define CCERASE '\x2b'
#define CCCREATE '\x2c'
#define CCREAD '\x2d'
#define CCCLOSE '\x2e'

#endif // OPCODE_H