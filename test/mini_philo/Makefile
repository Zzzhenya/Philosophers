CC		= cc

NAME	= philo

CFLAGS	= -Wall -Werror -Wextra -pthread -g -fsanitize=thread

SRCS	= 	main.c 

RM		= rm -rf

INCLUDE	= philo.h

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

.PHONY : all clean fclean re