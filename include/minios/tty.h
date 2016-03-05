#ifndef _TTY_H
#define _TTY_H

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long size_t;
#endif

extern void tty_init(void);
extern void cons_init(void);
extern void puts(const char * str);
extern void gotoxy(size_t x, size_t y);
extern void clrscr(void);
extern char toascii(unsigned char sc);
extern void kbd_intr(void);
extern void shell(void);
extern void prompt(void);
extern void proccmd(char * cmd);

#endif
