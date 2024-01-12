#include "libphilo.h"

long long get_milli_time(void)
{
	struct timeval	time;
	long long		militime;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	militime = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (militime);

}