#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <signal.h>
# define EAT 1
# define SLEEP 2
# define THINK 3
# define FORK 4
# define DIED 5
typedef struct s_philo
{
	int				index;
	int				ph_left;
	int				ph_right;
	unsigned int	t_start;
	unsigned int	t_limit;
	int				eat_count;
	int				is_dead;
	int				check_each_ph_eat;
	pid_t			pid;
	pthread_t		tid_health;
	pthread_t		tid_eat;
}				t_philo;

typedef struct s_var
{
	int				num_phil;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				count;
	unsigned int	start;
	int				error;
	sem_t			*mutex;
	sem_t			*die_mutex;
	sem_t			*msg_mutex;
	sem_t			*forks_mutex;
	sem_t			*eat;
}				t_var;

long long		ft_atoi(const char *str);
int				ft_isnum(int c);
t_var			*get_struct_var(t_var *ptr);
unsigned int	get_time(void);
t_philo			*init_philo_mutex(void);
void			aff_msg(t_philo *ph, int status);
void			take_forks(t_philo *ph);
void			eat_phil(t_philo *ph);
void			release_forks(void);
void			routine(t_philo *ph);
void			sleep_phil(t_philo *ph);
void			parse_data(int argc, char **argv);
unsigned int	get_time(void);
void			clear_destroy_ph(void);
void			clear(t_var *var, t_philo *philo);
#endif
