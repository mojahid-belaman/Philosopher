#include "philo_two.h"

void	*check_die_phil(void	*data)
{
	t_philo	*ph;

	ph = data;
	while (1)
	{
		sem_wait(ph->die_mutex);
		if (get_time() > ph->t_limit)
		{
			aff_msg(ph, DIED);
			ph->is_dead = 0;
			sem_post(ph->mutex);
			return (NULL);
		}
		sem_post(ph->die_mutex);
	}
	return (NULL);
}

void	check_health_phil(t_philo *ph)
{
	if (ph->is_dead)
	{
		pthread_create(&ph->tid_health, NULL, check_die_phil, ph);
		pthread_detach(ph->tid_health);
	}
}

void	*routine_phil(void	*data)
{
	t_philo *ph;
	t_var *var = get_struct_var(NULL);

	ph = data;
	ph->t_limit = ph->t_start + var->time_die;
	check_health_phil(ph);
	while (1)
	{
		take_forks(ph);
		eat_phil(ph);
		release_forks();
		if (ph->eat_count == 0)
		{
			ph->check_each_ph_eat = 1;
			break ;
		}
		sleep_phil(ph);
		aff_msg(ph, THINK);
		usleep(100);
	}
	return (NULL);
}