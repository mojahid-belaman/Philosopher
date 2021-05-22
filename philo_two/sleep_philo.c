#include "philo_two.h"

void	sleep_phil(t_philo *ph)
{
	int t_sleep;
	t_var *var = get_struct_var(NULL);
	if (ph->is_dead)
	{
		t_sleep = var->time_sleep * 1000;
		aff_msg(ph, SLEEP);
		usleep(t_sleep);
	}
}