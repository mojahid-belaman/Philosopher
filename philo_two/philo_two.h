#ifndef PHILO_TWO
# define PHILO_TWO

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <semaphore.h>
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
    unsigned int    t_start;
    unsigned int    t_limit;
    int             eat_count;
	int		        is_dead;
    pthread_t       tid;
    pthread_t       tid_health;
    pthread_t       tid_eat;
    sem_t           *die_mutex;
    sem_t           *mutex;
    int             check_each_ph_eat;
}               t_philo;


typedef struct s_var
{
    int 	        num_phil;
    int 	        time_die;
    int 	        time_eat;
    int 	        time_sleep;
    int             count;
    unsigned int    start;
    int             error;
    sem_t           *forks_mutex;
    sem_t           *msg_mutex;
}              t_var;

long long       ft_atoi(const char *str);
size_t	        ft_strlen(const char *str);
int             ft_isnum(int c);
void            ft_putchar_fd(char c, int fd);
void            ft_putnbr_fd(int n, int fd);
void            ft_putstr_fd(char *s, int fd);
t_var           *get_struct_var(t_var *ptr);
unsigned int	get_time();
t_philo         *init_philo_mutex();
void            aff_msg(t_philo *ph, int status);
void            take_forks(t_philo *ph);
void            eat_phil(t_philo *ph);
void            release_forks();
void            *routine_phil(void	*data);
void            sleep_phil(t_philo *ph);
void            parse_data(int argc, char **argv);
unsigned int    get_time();
#endif     
      