CC		= cc

NAME	= philo

CFLAGS	= -Wall -Werror -Wextra -pthread

SRCS	= main.c

OBJS	= $(SRCS:.c=.o)


all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $^

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re