#ifndef ERRORS_H
# define ERRORS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

void	err_exit(char *str);
void	errno_exit(int errno, char *str);

#endif