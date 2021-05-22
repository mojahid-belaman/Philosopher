#include "philo_two.h"

t_philo    *init_philo_mutex()
{
    t_philo	*philo;
	t_var *var = get_struct_var(NULL);
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * var->num_phil);
	sem_unlink("forks");
	sem_unlink("die");
	sem_unlink("hold_pro");
	var->forks_mutex = sem_open("forks", O_CREAT, 0600, var->num_phil);
	philo->die_mutex = sem_open("die", O_CREAT, 0600, 1);
	philo->mutex = sem_open("hold_pro", O_CREAT, 0600, 1);
	i = -1;
	while (++i < var->num_phil)
	{
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