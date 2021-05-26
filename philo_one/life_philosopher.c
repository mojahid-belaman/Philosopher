#include "philo_one.h"

void	*check_die_phil(void	*data)
{
	t_philo	*ph;
	t_var	*var;

	var = get_struct_var(NULL);
	ph = data;
	while (1)
	{
		pthread_mutex_lock(&var->die_mutex);
		if (get_time() > ph->t_limit)
		{
			aff_msg(ph, DIED);
			ph->is_dead = 0;
			pthread_mutex_unlock(&var->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&var->die_mutex);
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
	t_philo	*ph;
	t_var	*var;

	var = get_struct_var(NULL);
	ph = (t_philo *)data;
	ph->t_start = get_time();
	ph->t_limit = ph->t_start + var->time_die;
	check_health_phil(ph);
	while (1)
	{
		take_forks(ph);
		eat_phil(ph);
		release_forks(ph);
		if (ph->eat_count == 0)
		{
			ph->check_each_ph_eat = 1;
			break ;
		}
		sleep_phil(ph);
		aff_msg(ph, THINK);
	}
	return (NULL);
}
