CC		= cc

NAME	= philo

CFLAGS	= -Wall -Werror -Wextra -pthread -g

SRCS	= main.c err_exit.c errno_exit.c

RM		= rm -rf

INCLUDE	= libphilo.h errors.h

OBJS	= $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $^
	@echo "...Linking objs."

%.o : %.c $(INCLUDE)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "...Compiling $(notdir $<)."

clean :
	@$(RM) $(OBJS)
	@echo "...Removing objs."

fclean : clean
	@$(RM) $(NAME)
	@echo "...Removing binary."

re : fclean all

debug:
	make re
	export MallocStackLogging=1
	export MallocStackLoggingNoCompact=1
	leaks --atExit -- ./$(NAME) > log.txt 2>&1
	make fclean

.PHONY : all clean fclean re debug