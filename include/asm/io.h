#define inb(_port) ({\
	unsigned char _rval;\
	__asm__ __volatile__ ("inb %1, %0"\
	:"=a"((unsigned char)_rval) : "d" ((unsigned short)_port)); \
	_rval;	\
	})

#define outb(_port, _data)\
	__asm__ __volatile__ ("outb %1, %0" : : \
	"d" ((unsigned short)_port), "a" ((unsigned char)_data));
