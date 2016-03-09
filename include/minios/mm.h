#ifndef _MM_H
#define _MM_H

extern void setup_paging(void);
extern void load_page_directory(unsigned long *);
extern void enable_paging(void);

#endif
