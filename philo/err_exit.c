#include "errors.h"

/* Writes the error message str to stderror and exit */
static int get_strlen(char *str)
{
	int len;

	len = 0;
	if (!str)
		return (len);
	while (str[len])
		len ++;
	return (len);
}

static void print_message(char *str)
{
	int len;

	len = get_strlen(str);
	write (2, str, len);
}

void	err_exit(char *str)
{
	print_message(str);
	exit (1);
}