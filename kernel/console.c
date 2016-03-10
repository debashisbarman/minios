/* 
 * console.c
 *
 * This file contains the console io functions. I like this version
 * of console.c for its clean implementation.
 */
#include <stddef.h>
#include <string.h>
#include <stdarg.h>
#include <minios/tty.h>
#include <asm/io.h>
#include <asm/system.h>

#define CSR_COMMAND_PORT	0x3D4
#define CSR_DATA_PORT		0x3D5

#define CSR_HIGH_BYTE	0xE
#define CSR_LOW_BYTE	0xF

#define NR_COLUMNS	80
#define NR_LINES	25

#define VIDEO_ADDR	0xB8000

static unsigned short * video;
static unsigned char attr = 0x07;
long pos;
size_t csr_x = 0, csr_y = 0;

void gotoxy(size_t x, size_t y)
{
	csr_x = x;
	csr_y = y;

	pos = csr_y * NR_COLUMNS + csr_x;

	outb(CSR_COMMAND_PORT, CSR_HIGH_BYTE);
	outb(CSR_DATA_PORT, (unsigned char )(pos >> 8));
	outb(CSR_COMMAND_PORT, CSR_LOW_BYTE);
	outb(CSR_DATA_PORT, (unsigned char)pos);
}

void clrscr(void)
{
	for (size_t i = 0; i < NR_COLUMNS * NR_LINES; i++)
		video[i] = ' ' | attr << 8;

	gotoxy(0, 0);
}

void puts(const char * str)
{
	size_t c;

	cli();

	while ((c = (unsigned char)(*str++)) != 0) {
		switch(c) {
			case 000 :	break;

			case '\b' :	if(csr_x) {
						csr_x--;
						pos = csr_y * NR_COLUMNS + csr_x;
						video[pos] = ' ' | (attr << 8);
					}
					break;

			case '\t' :	csr_x = (csr_x + 8) & ~ (8 - 1);
					if (csr_x > NR_COLUMNS) {
						csr_x = 0;
						csr_y++;
					}
					break;

			case '\r' :	csr_x = 0;
					break;

			case '\n' :	csr_x = 0;
					csr_y++;
					break;

			default:	pos = csr_y * NR_COLUMNS + csr_x;
					video[pos] = c | (attr << 8);
					csr_x++;
					if (csr_x > NR_COLUMNS) {
						csr_x = 0;
						csr_y++;
					}			
		}

		if (csr_y >= NR_LINES) {
                	memcpy((void*)VIDEO_ADDR, (void*)(VIDEO_ADDR + 160), NR_COLUMNS * NR_LINES * 2);
                        for (c = 0; c < 80; c++)
                        	video[NR_COLUMNS * (NR_LINES - 1) + c] = ' ' | (attr << 8);
                        csr_y = NR_LINES-1;
		}
	}

	/* Update cursor position */
        pos = csr_y * NR_COLUMNS + csr_x;

	outb(CSR_COMMAND_PORT, CSR_HIGH_BYTE);
	outb(CSR_DATA_PORT, (unsigned char )(pos >> 8));
	outb(CSR_COMMAND_PORT, CSR_LOW_BYTE);
	outb(CSR_DATA_PORT, (unsigned char)pos);

	sti();
}

void cons_init(void)
{
	video = (unsigned short *)VIDEO_ADDR;
	clrscr();
}
