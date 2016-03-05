#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <minios/mm.h>
#include <minios/kernel.h>

#define PDT_SIZE sizeof(page_directory_t)
#define PTE_SIZE sizeof(page_table_t)

#define PS_4KB 0x0
#define PS_4MB 0x1

#define USER_PRIVILEDGE	0x7

#define LOW_MEM	0x1000000
#define HIGH_MEM 0xffffffff

page_directory_t *kd = 0;
page_directory_t *cd = 0;

/*
 * Get physical address of first free page, and mark it
 * used.
 */
static inline size_t get_free_page(void)
{
	/* FIXME: please make this code more beautiful */
	for (size_t i = 0; i < index(nr_frames); i++) {
		if (mem_map[i] != HIGH_MEM) {
			for (size_t j = 0; j < 32; j++) {
				if (!(mem_map[i] & (0x1 << j)))
					return i * 32 + j;
			}
		}
	}
	return (size_t)-1;
}

/*
 * Retrieves a pointer to the page required.
 * If flag == 1, if the page-table in which this page should
 * reside isn't created, create it!
 */
static inline page_t * get_page(size_t addr, size_t flag, page_directory_t * dir)
{
	addr /= PAGE_SIZE;
	size_t i = addr / NUM_ENTRIES;
	if (dir->tables[i])
		return &dir->tables[i]->pages[addr % NUM_ENTRIES];
	else if (flag) {
		size_t temp;
		dir->tables[i] = (page_table_t *)kmalloc_align(PTE_SIZE, (size_t) &temp);
		memset(dir->tables[i], 0, PAGE_SIZE);
		dir->paddrspc[i] = temp | USER_PRIVILEDGE;
		return &dir->tables[i]->pages[addr % NUM_ENTRIES];
	} else
		return 0;
}

/* Allocate a frame in physical memory */
static inline void alloc_frame(page_t * page, size_t kpl, size_t rw)
{
	if (page->frame != 0)
		return;
	else {
		size_t i = get_free_page();
		if (i == (size_t)-1)
			panic("No free frames!");
		set_bit(i * PAGE_SIZE);
		page->present = 1;
		page->rw = rw ? 1 : 0;
		page->user = kpl ? 0 : 1;
		page->frame = i;
	}
}

/* Free a page from physical memory */
static inline void free_frame(page_t * page)
{
	size_t frame;
	if (!(frame = page->frame))
		return;
	else {
		unset_bit(frame);
		page->frame = 0x0;
	}
}

/*
 * Sets up the environment, page directories etc and
 * enables paging.
 */
void setup_paging(void)
{
	nr_frames = LOW_MEM / PAGE_SIZE;
	mem_map = (size_t *)kmalloc(index(nr_frames));
	memset(mem_map, 0, index(nr_frames));

	kd = (page_directory_t *)kmalloc(PDT_SIZE);
	memset(kd, 0, sizeof(PDT_SIZE));
	cd = kd;

	size_t i = 0;
	while (i < placement_address) {
		alloc_frame(get_page(i, 1, kd), 0, 0);
		i += PAGE_SIZE;
	}

	load_page_directory(kd->paddrspc);

	enable_paging();
}
