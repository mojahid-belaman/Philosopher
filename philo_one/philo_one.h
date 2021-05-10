#ifndef PHILO_ONE
# define PHILO_ONE

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
# define EAT 1
# define SLEEP 2
# define THINK 3
# define FORK 4
# define DIED 5
typedef struct s_var
{
    int 	        num_phil;
    int 	        time_die;
    int 	        time_eat;
    int 	        time_sleep;
	int		        is_died;
    int             count;
    unsigned    long    t_start;
    unsigned    long    limit;
    int 		    index;
    int 		    ph_eat;
    int 		    ph_left;
    int			    ph_right;
    int			    eat_count;
    pthread_t       tid;
    pthread_mutex_t *forks_mutex;
    pthread_mutex_t msg_mutex;

}              t_var;

long long   ft_atoi(const char *str);
void	    ft_putstr_fd(char *s, int fd);
size_t	    ft_strlen(const char *str);
int         ft_isnum(int c);
void        ft_putchar_fd(char c, int fd);
void        ft_putnbr_fd(int n, int fd);
#endif
