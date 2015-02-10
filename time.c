#include<time.h>

unsigned long ssecond,nowtime;
unsigned long seed;

long gettime()
{
	time_t t;
	time(&t);
	struct tm *local;
	local = localtime(&t);
	local->tm_mon++;
	ssecond = (long)local->tm_sec*100+local->tm_sec+36923;
	nowtime = local->tm_sec + local->tm_min*100 + local->tm_hour*10000 + local->tm_mday*1000000 + local->tm_mon*100000000;
	return nowtime;
}

//seed = gettime()

