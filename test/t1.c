#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main (void)
{
	int i = 0;
	int k = 0;

	while (i < 500)
	{
		k = rand();
		printf("%d: rand: %d res: %d\n", i, k, (k % 12)/2 );
		i ++;
	}
	return (0);
}