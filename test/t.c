#include <stdio.h>

int main (void)
{
	int i = 0;
	int j;

	while (i < 10)
	{
		j = 0;
		while (j < 5)
		{
			if (j == 3)
			{
				printf("i: %d j :%d\n", i , j);
				break;
				return (1);
			}
			j ++;
		}
		i ++;
	}
	return (0);
}