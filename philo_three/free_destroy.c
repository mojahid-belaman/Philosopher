#include "philo_three.h"

void	clear_destroy_ph(void)
{
	sem_unlink("forks");
	sem_unlink("die");
	sem_unlink("msg");
	sem_unlink("hold_pro");
}
