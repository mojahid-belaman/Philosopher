#include "philo_two.h"

void	aff_msg(t_philo *ph, int status)
{
	t_var *var = get_struct_var(NULL);

	sem_wait(var->msg_mutex);
	if (status == FORK)
		printf("%u\t%d has taken a fork\n", get_time() - var->start, ph->index + 1);
	else if (status == EAT)
		printf("%u\t%d is eating\n", get_time() - var->start, ph->index + 1);
	else if (status == SLEEP)
		printf("%u\t%d is sleeping\n", get_time() - var->start, ph->index + 1);
	else if (status == THINK)
		printf("%u\t%d is thinking\n", get_time() - var->start, ph->index + 1);
	else if (status == DIED)
		printf("%u\t%d died\n", get_time() - var->start, ph->index + 1);
	if (status != DIED)
		sem_post(var->msg_mutex);
}