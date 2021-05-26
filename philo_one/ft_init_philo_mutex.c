#include "philo_one.h"

void	init_each_philo(t_philo *philo, t_var *var, int i)
{
	pthread_mutex_init(&var->forks_mutex[i], NULL);
	philo[i].index = i;
	philo[i].ph_left = i;
	philo[i].ph_right = (i + 1) % var->num_phil;
	philo[i].is_dead = 1;
	if (var->count == -1)
		philo[i].eat_count = -1;
	else
		philo[i].eat_count = var->count;
	philo[i].check_each_ph_eat = 0;
}

t_philo	*init_philo_mutex(void)
{
	t_philo	*philo;
	t_var	*var;
	int		i;

	var = get_struct_var(NULL);
	philo = (t_philo *)malloc(sizeof(t_philo) * var->num_phil);
	var->forks_mutex = malloc(sizeof(pthread_mutex_t) * var->num_phil);
	pthread_mutex_init(&var->mutex, NULL);
	pthread_mutex_init(&var->die_mutex, NULL);
	pthread_mutex_init(&var->msg_mutex, NULL);
	i = -1;
	while (++i < var->num_phil)
		init_each_philo(philo, var, i);
	var->start = get_time();
	return (philo);
}
