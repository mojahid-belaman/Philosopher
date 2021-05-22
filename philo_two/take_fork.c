#include "philo_two.h"

void	take_forks(t_philo *ph)
{
	t_var *var;
	
	var = get_struct_var(NULL);
	if (ph->is_dead)
	{
		sem_wait(var->forks_mutex);
		aff_msg(ph, FORK);
		sem_wait(var->forks_mutex);
		aff_msg(ph, FORK);
	}
}

void	release_forks()
{
	t_var *var;
	
	var = get_struct_var(NULL);
	sem_post(var->forks_mutex);
	sem_post(var->forks_mutex);
}