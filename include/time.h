#ifndef _TIME_H
#define _TIME_H

typedef struct {
	int sec;
	int min;
	int hour;
	int dayofweek;
	int day;
	int month;
	int year;
} time_t;

extern void kernel_mktime(time_t *);

#endif
