#ifndef _KERNEL_H
#define _KERNEL_H

#include <stdarg.h>

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long size_t;
#endif

#ifndef VERSION
#define VERSION "0.0.1"
#endif

extern int vsprintf(char *buf, const char *fmt, va_list args);
extern size_t printk(const char *fmt, ...);
extern void panic(const char * str);
extern void exit(void);
extern void trap_init(void);
extern void timer_wait(size_t ticks);

#endif
