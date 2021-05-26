#include "philo_one.h"

void	take_forks(t_philo *ph)
{
	t_var	*var;

	var = get_struct_var(NULL);
	if (ph->is_dead)
	{
		pthread_mutex_lock(&var->forks_mutex[ph->ph_left]);
		aff_msg(ph, FORK);
		pthread_mutex_lock(&var->forks_mutex[ph->ph_right]);
		aff_msg(ph, FORK);
	}
}

void	release_forks(t_philo *ph)
{
	t_var	*var;

	var = get_struct_var(NULL);
	pthread_mutex_unlock(&var->forks_mutex[ph->ph_left]);
	pthread_mutex_unlock(&var->forks_mutex[ph->ph_right]);
}
