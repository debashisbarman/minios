#ifndef _TIME_H
#define _TIME_H

struct time{
	int sec;
	int min;
	int hour;
	int dayofweek;
	int day;
	int month;
	int year;
};

extern void kernel_mktime(struct time *);

#endif
