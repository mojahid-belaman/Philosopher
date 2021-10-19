NAME = philo_three

CFLAGS = -Wall -Wextra -Werror

SRC =	ft_atoi.c\
		ft_isalnum.c\
		ft_init_philo_mutex.c\
		parse.c\
		life_philosopher.c\
		msg_print.c\
		sleep_philo.c\
		take_fork.c\
		eat_philo.c\
		time.c\
		free_destroy.c\
		clear.c\
		main.c
OBJ = $(SRC:.c=.o)

bold = $(shell tput bold)

all : $(NAME)

$(NAME) : $(OBJ)
	@gcc $(CFLAGS) $(OBJ) -lpthread -o $(NAME)
	@echo "${bold}... DONE ...${ED}"

%.o : %.c
	@gcc $(CFLAGS) -c $< -o $@

clean :
	@rm -f $(OBJ)
	@echo "${bold}REMOVE LIBRARY...[OK]${ED}"

fclean : clean
	@rm -f $(NAME)
	@echo "${bold}REMOVE EXECUTION...[OK]${ED}"

re : fclean all


