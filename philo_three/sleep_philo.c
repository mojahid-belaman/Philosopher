#include "philo_three.h"

void	sleep_phil(t_philo *ph)
{
	t_var	*var;
	int		t_sleep;

	var = get_struct_var(NULL);
	if (ph->is_dead)
	{
		t_sleep = var->time_sleep * 1000;
		aff_msg(ph, SLEEP);
		usleep(t_sleep);
	}
}
