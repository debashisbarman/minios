#include <stddef.h>
#include <stdarg.h>
#include <minios/tty.h>
#include <minios/kernel.h>

static char buf[1024];

size_t printk(const char * fmt, ...)
{
	va_list args;
        size_t i;

        va_start(args, fmt);
        i = vsprintf(buf, fmt, args);
        va_end(args);

        puts(buf);
        return i;
}
