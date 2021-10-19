#include "philo_three.h"

void	init_each_philo(t_philo *philo, t_var *var, int i)
{
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
	sem_unlink("forks");
	sem_unlink("die");
	sem_unlink("msg");
	sem_unlink("hold_pro");
	sem_unlink("eat_sem");
	var->forks_mutex = sem_open("forks", O_CREAT, 0600, var->num_phil);
	var->die_mutex = sem_open("die", O_CREAT, 0600, 1);
	var->msg_mutex = sem_open("msg", O_CREAT, 0600, 1);
	var->mutex = sem_open("hold_pro", O_CREAT, 0600, 1);
	var->eat = sem_open("eat_sem", O_CREAT, 0600, 0);
	i = -1;
	while (++i < var->num_phil)
		init_each_philo(philo, var, i);
	var->start = get_time();
	return (philo);
}
