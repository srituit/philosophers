NAME	=	philo
SRCS	=	main.c l_philo.c utils.c
OBJS	=	$(SRCS:.c=.o)
CC	=	gcc
FLAGS	=	-Wall -Werror -Wextra

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean:		clean
	rm -f $(NAME)

re:		fclean all

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)
.PHONY:	clean fclean re 
