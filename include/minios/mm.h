#ifndef _MM_H
#define _MM_H

#define index(n) (n / 32)
#define offset(n) (n % 32)

#define set_bit(bit) \
	mem_map[index(bit)] |= (1 << offset(bit))

#define unset_bit(bit)\
	mem_map[index(bit)] &= ~(1 << offset(bit))

#define test_bit(bit)\
	return mem_map[index(bit)] & (1 << offset(bit))

#define NUM_ENTRIES 1024

#define PAGE_SIZE 4096

typedef struct {
	size_t present : 1, rw : 1, user : 1, accessed : 1;
	size_t dirty : 1, unused : 1, frame : 20;
} page_t;

typedef struct {
	page_t pages[NUM_ENTRIES];
} page_table_t;

typedef struct {
	page_table_t * tables[NUM_ENTRIES];
	size_t paddrspc[NUM_ENTRIES], paddr;
} page_directory_t;

size_t * mem_map;
size_t nr_frames;
size_t placement_address;

/* Physical memory allocation */
static inline size_t kmalloc(size_t size)
{
	size_t temp = placement_address;
	placement_address += size;
	return temp;
}

static inline size_t kmalloc_align(size_t size, size_t align)
{
	if (align == 1 && (placement_address & 0xfffff000)) {
		placement_address &= 0xfffff000;
		placement_address += PAGE_SIZE;
	}
	size_t temp = placement_address;
	placement_address += size;
	return temp;
}

extern void setup_paging(void);
extern void load_page_directory(size_t *);
extern void enable_paging(void);

#endif
