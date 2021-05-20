#include "philo_one.h"

t_philo    *init_philo_mutex()
{
    t_philo	*philo;
	t_var *var = get_struct_var(NULL);
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * var->num_phil);
	var->forks_mutex = malloc(sizeof(pthread_mutex_t) * var->num_phil);
	philo->die_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philo->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->die_mutex, NULL);
	pthread_mutex_init(philo->mutex, NULL);
	pthread_mutex_init(&var->msg_mutex, NULL);
	i = -1;
	while (++i < var->num_phil)
	{
		pthread_mutex_init(&var->forks_mutex[i], NULL);
		philo[i].index = i;
		philo[i].ph_left = i;
		philo[i].ph_right = (i + 1) % var->num_phil;
		philo[i].t_start = get_time();
		philo[i].die_mutex = philo->die_mutex;
		philo[i].mutex = philo->mutex;
    	philo[i].is_dead = 1;
		if (var->count == -1)
			philo[i].eat_count = -1;
		else
			philo[i].eat_count = var->count;
		philo[i].check_each_ph_eat = 0;
	}
	var->start = get_time();
    return (philo);
}