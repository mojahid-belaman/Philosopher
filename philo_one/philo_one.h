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
typedef struct s_philo
{
    int 		    index;
    int 		    ph_left;
    int			    ph_right;
    int             check_eat;
    unsigned int    t_start;
    unsigned int    t_limit;
    int             eat_count;
    pthread_t       tid;
    pthread_t       tid_health;
    pthread_mutex_t *die_mutex;
}               t_philo;


typedef struct s_var
{
    int 	        num_phil;
    int 	        time_die;
    int 	        time_eat;
    int 	        time_sleep;
	int		        is_dead;
    int             count;
    unsigned int    start;
    int             all_phil_eat;
    pthread_mutex_t *forks_mutex;
    pthread_mutex_t msg_mutex;
}              t_var;

long long   ft_atoi(const char *str);
size_t	    ft_strlen(const char *str);
int         ft_isnum(int c);
void        ft_putchar_fd(char c, int fd);
void        ft_putnbr_fd(int n, int fd);
void        ft_putstr_fd(char *s, int fd);
#endif
