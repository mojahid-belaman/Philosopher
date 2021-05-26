#include "philo_one.h"

unsigned int	diff_time(t_var *var)
{
	return (get_time() - var->start);
}

void	aff_msg(t_philo *ph, int status)
{
	t_var	*var;

	var = get_struct_var(NULL);
	pthread_mutex_lock(&var->msg_mutex);
	if (status == FORK)
		printf("%u\t%d has taken a fork\n", diff_time(var), ph->index + 1);
	else if (status == EAT)
		printf("%u\t%d is eating\n", diff_time(var), ph->index + 1);
	else if (status == SLEEP)
		printf("%u\t%d is sleeping\n", diff_time(var), ph->index + 1);
	else if (status == THINK)
		printf("%u\t%d is thinking\n", diff_time(var), ph->index + 1);
	else if (status == DIED)
		printf("%u\t%d died\n", diff_time(var), ph->index + 1);
	if (status != DIED)
		pthread_mutex_unlock(&var->msg_mutex);
}
