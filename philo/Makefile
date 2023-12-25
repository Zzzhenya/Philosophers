CC		= cc

NAME	= philo

CFLAGS	= -Wall -Werror -Wextra -pthread

SRCS	= main.c

RM		= rm -rf

OBJS	= $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $^
	@echo "...Linking objs."

%.o : %.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "...Compiling srcs."

clean :
	@$(RM) $(OBJS)
	@echo "...Removing objs."

fclean : clean
	@$(RM) $(NAME)
	@echo "...Removing binary."

re : fclean all

.PHONY : all clean fclean re