#ifndef PHILO_ONE
# define PHILO_ONE

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_phil
{
    int 		    index;
    int 		    ph_eat;
    int 		    ph_left;
    int			    ph_right;
    int			    eat_count;
    pthread_t       tid;
	pthread_mutex_t	mutex;

}              t_phil;

typedef struct s_var
{
    int 	num_phil;
    int 	time_die;
    int 	time_eat;
    int 	time_sleep;
	int		some_die;
	t_phil	*phil;

}              t_var;

long long   ft_atoi(const char *str);
void	    ft_putstr_fd(char *s, int fd);
size_t	    ft_strlen(const char *str);
int         ft_isnum(int c);
#endif
