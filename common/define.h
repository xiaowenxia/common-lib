#ifndef __DEFINE_H__
#define __DEFINE_H__

#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#include "string.h"

/* combine two symbol to one*/
#define COMBINE_SYM(x,y)        x##y

/* change a variable to string ,just for debug */
#define VAR2STRING(x)       #x

/* change a variable(char) to char ,just for debug */
//#define VAR2CHAR(x)     #@x

/* _FILE_ include the path,just like:/opt/workspace/c/helloworld/main.c
 * filename() can delete the path ,just like shell:basename command
 * "\\" for windows "\/ "for linux */
//#define filename(x) strrchr(x,'\/')?strrchr(x,'\/')+1:x
#define BASENAME(x)     strrchr(x,'\\')?strrchr(x,'\\')+1:x

/* get the value in the memery */
#define MEM_B(x)        (*((byte *)(x))) 
#define MEM_W(x)        (*((word *)(x)))

/* get the offset(field) in the struct(type),set the address(0) to 
 * the struct type, and return the field address */
#define OFFSETOF(type,field)        ((size_t)&((type *)0)->field)

/* get the number of array element */
#define ARRAY_SIZE(x) ( sizeof((x)) / sizeof((x[0])))

/* get ads value */
#define CS_ABS(x) (x)>=0?(x):(-x)

/* redefine malloc function, thread safe */
#define xx_malloc  malloc
#define xx_free    free

/* redefine printf function */
#define xx_printf  printf

/* assert function */
void cs_assert_handler(const unsigned char* ex_string, const char* func, int line);

#define ASSERT(EX)      \
if (!(EX))      \
{       \
    cs_assert_handler(VAR2STRING(EX), __func__, __LINE__);     \
}else{      \
}

/* dump hex data stream */
#define DUMP_BUFFER(buf, len)                                   \
    do {                                                        \
        int _i;                                                 \
        if (!buf || len <= 0) {                                 \
            break;                                              \
        }                                                       \
        for (_i = 0; _i < len; _i++) {                          \
            if (!(_i%16))                                       \
                xx_printf("\n%p: ", buf+_i);                       \
            xx_printf("%02x ", (*((char *)buf + _i)) & 0xff);      \
        }                                                       \
        xx_printf("\n");                                           \
    } while (0)

#endif /* __DEFINE_H__ */
