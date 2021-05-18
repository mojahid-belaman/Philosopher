NAME = philo_one

CFLAGS = -Wall -Wextra -Werror

SRC =	ft_atoi.c\
		ft_isalnum.c\
		ft_strlen.c\
		ft_putchar_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
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


