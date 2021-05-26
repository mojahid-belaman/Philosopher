#include "philo_one.h"

void	clear_destroy_ph(t_philo *philo)
{
	int		i;
	t_var	*var;

	i = -1;
	var = get_struct_var(NULL);
	while (++i < var->num_phil)
		pthread_mutex_destroy(var->forks_mutex);
	free(philo);
}
