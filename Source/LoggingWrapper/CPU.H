

#ifndef _CPU_H_
#define _CPU_H_     0

#undef PACKED1
#define PACKED1
#undef PACKED2
#define PACKED2
#undef PACKED4
#define PACKED4

#ifdef WIN32
#include "wtypes.h"
#endif



//---------------------------------------------------------------------------------
#ifdef  M68360              /* Motorola 68360 */

#define _far
#define CONST_TEXT
#define MENU_TEXT

// Macros
#ifndef OUT8        // If these have not already been defined
#define OUT8(x,y)           (*((volatile unsigned char *)x) = y)
#define OUT16(x,y)          (*((volatile unsigned short *)x) = y)
#define OUT32(x,y)          (*((volatile unsigned long *)x) = y)
#define IN8(x)              (*((volatile unsigned char *)(x)))
#define IN16(x)             (*((volatile unsigned short *)(x)))
#define IN32(x)             (*((volatile unsigned long *)(x)))
#endif  //OUT8

#define ARC_OUT8(x,y)       (*((volatile unsigned char *)(ARCNET_PORT_BASE + x)) = y)
#define ARC_IN8(x)          (*((volatile unsigned char *)(ARCNET_PORT_BASE + x)))

#define ENABLE_INTERUPT()   _Enable()
#define DISABLE_INTERUPT()  _Disable()

#define PACKED1
#define PACKED2
#define PACKED4

typedef signed char         SIGNED8;
typedef signed short        SIGNED16;
typedef signed int          SIGNED32;
typedef unsigned char       UNSIGNED8;
typedef unsigned short      UNSIGNED16;
typedef unsigned int        UNSIGNED32;
typedef char*               CALLBACK_DATA_PTR;

//---------------------------------------------------------------------------------
#elif defined PPC603_VXWORKS            /* VxWorks for PowerPC 603 Family */

#define _far
#define CONST_TEXT
#define MENU_TEXT

#undef ONCE
#undef PACKED
#define PACKED      __attribute__ ((aligned (2), packed))   /* 2-byte boundary packing */
#undef PACKED1
#define PACKED1     __attribute__ ((aligned (1), packed))   /* 1-byte boundary packing */
#undef PACKED2
#define PACKED2     __attribute__ ((aligned (2), packed))   /* 2-byte boundary packing */
#undef PACKED4
#define PACKED4     __attribute__ ((aligned (4), packed))   /* 4-byte boundary packing */

typedef signed char     SIGNED8;
typedef signed short    SIGNED16;
typedef signed int      SIGNED32;
typedef unsigned char   UNSIGNED8;
typedef unsigned short  UNSIGNED16;
typedef unsigned int    UNSIGNED32;


//---------------------------------------------------------------------------------
#else               /* Intel */

//---------------------------------------------------------------------------------
#if defined VXWORKS  /* VxWorks for Intel */

#define _far
#define CONST_TEXT
#define MENU_TEXT


#define ARC_OUT8(x,y)       sysOutByte((int)(x), (char)(y))
#define ARC_IN8(x)          sysInByte((int)(x))

#define DISABLE_INTERUPT()  intLock()
#define ENABLE_INTERUPT(x)  intUnlock(x)

#define PACKED1
#define PACKED2
#define PACKED4

//---------------------------------------------------------------------------------
#elif defined WIN32 || defined WIN32_LEAN_AND_MEAN
#define CONST_TEXT
#define MENU_TEXT

//Macros
#define OPT_PAGE
#undef ONCE
#define ONCE once
#undef PACKED
#define PACKED      pack (pop)
#undef PACKED1
#define PACKED1     pack (push,1)
#undef PACKED2
#define PACKED2     pack (push,2)
#undef PACKED4
#define PACKED4     pack (push,4)

typedef signed char         SIGNED8;
typedef signed short int    SIGNED16;
typedef signed int          SIGNED32;
typedef unsigned char       UNSIGNED8;
typedef unsigned short int  UNSIGNED16;
typedef unsigned int        UNSIGNED32;
typedef UNSIGNED32*         CALLBACK_DATA_PTR;

#else           /* Non-VxWorks, non-Windos Intel CPUs */
#define CONST_TEXT  __based(__segname("CONST_TEXT"))
#define MENU_TEXT   __based(__segname("MENU_TEXT"))

//Macros
#define DISABLE_INTERUPT(); _disable();
#define ENABLE_INTERUPT();  _enable();
#define IN8(r)              _inp(r)
#define IN16(r)             _inpw(r)
#define OUT8(r,d)           _outp(r,d)
#define OUT16(r,d)          _outpw(r,d)

#define PACKED1
#define PACKED2
#define PACKED4

typedef char                SIGNED8;
typedef int                 SIGNED16;
typedef long                SIGNED32;
typedef unsigned char       UNSIGNED8;
typedef unsigned int        UNSIGNED16;
typedef unsigned long       UNSIGNED32;
typedef UNSIGNED32*         CALLBACK_DATA_PTR;

#endif /* end of Intel variants */

#endif  /* end of CPU variants */

#endif      // _CPU_H_
