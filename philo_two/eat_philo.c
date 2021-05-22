#include "philo_two.h"

void	eat_phil(t_philo *ph)
{
	int	t_eat;

	t_var *var = get_struct_var(NULL);
	t_eat = var->time_eat * 1000;
	if (ph->is_dead)
	{
		aff_msg(ph, EAT);
		if (ph->eat_count != -1)
			ph->eat_count--;
		ph->t_start = get_time();
		ph->t_limit = ph->t_start + var->time_die;
		usleep(t_eat);
	}
}
