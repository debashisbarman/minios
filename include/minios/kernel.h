#ifndef _KERNEL_H
#define _KERNEL_H

extern void printk(char *fmt, ...);
extern void panic(const char * str);
extern void exit(void);
extern void clrscr(void);
extern void timer_intr(void);

#endif
