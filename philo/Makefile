CC		= cc

NAME	= philo

CFLAGS	= -Wall -Werror -Wextra -pthread

CFLAGS 	+= -g -fsanitize=thread 

SRCS	= 	main.c parse_and_store.c \
			print_message.c init.c

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

race:
	make re

#debug:
#	make re
#	export MallocStackLogging=1
#	export MallocStackLoggingNoCompact=1
#	leaks --atExit -- ./$(NAME) > log.txt 2>&1
#	make fclean

.PHONY : all clean fclean re debug race