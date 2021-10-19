#include "philo_three.h"

void	clear(t_var *var, t_philo *philo)
{
	int	status;
	int	i;

	sem_unlink("forks");
	sem_unlink("die");
	sem_unlink("msg");
	sem_unlink("hold_pro");
	i = -1;
	while (++i < var->num_phil)
	{
		waitpid(philo[i].pid, &status, 0);
		kill(philo[i].pid, SIGKILL);
	}
	free(philo);
}
