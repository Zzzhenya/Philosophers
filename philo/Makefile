# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sde-silv <sde-silv@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 11:55:57 by sde-silv          #+#    #+#              #
#    Updated: 2024/02/15 13:54:32 by sde-silv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc

NAME	= philo

CFLAGS	= -Wall -Werror -Wextra -pthread

CFLAGS += -g -fsanitize=thread

SRCS	= 	main.c input_check.c \
			print_error.c init_struct.c \
			debug.c mtx_actions.c \
			init_dining.c \
			utils.c routine.c eat_routine.c\
			monitor.c \

RM		= rm -rf

INCLUDE	= libphilo.h

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

#debug:
#	make re
#	export MallocStackLogging=1
#	export MallocStackLoggingNoCompact=1
#	leaks --atExit -- ./$(NAME) > log.txt 2>&1
#	make fclean

.PHONY : all clean fclean re debug
