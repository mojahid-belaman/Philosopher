#include "philo_two.h"

t_var *get_struct_var(t_var *ptr)
{
    static t_var *tmp;

    if (ptr)
        tmp = ptr;
    return (tmp);
}

void	*check_eat_count(void *arg)
{
	t_philo	*ph;
	t_var	*var;
	int		i;
	int		all_philo_eat;
	
	ph = (t_philo *)arg;
	var = get_struct_var(NULL);
	i = 0;
	all_philo_eat = 0;
	while (1)
	{
		if (i == var->num_phil)
			i = 0;
		if (ph[i].eat_count == 0 && ph[i].check_each_ph_eat == 1)
		{
			ph[i].eat_count = -1;
			all_philo_eat++;
		}
		if (all_philo_eat == var->num_phil)
			break ;
		i++;
	}
	sem_wait(var->msg_mutex);
	printf("sumilation stoped\n");
	sem_post(ph->mutex);
	return (NULL);
}

void	phil_init_start()
{
	t_philo *philo;
	t_var	*var;
	int		i;

	var = get_struct_var(NULL);
	philo = init_philo_mutex();
	i = -1;
	sem_wait(philo->mutex);
	if (philo->eat_count > 0)
	{
		pthread_create(&philo->tid_eat, NULL, check_eat_count, philo);
		pthread_detach(philo->tid_eat);
	}
	while (++i < var->num_phil)
	{
		pthread_create(&philo[i].tid, NULL, routine_phil, &philo[i]);
		pthread_detach(philo[i].tid);
	}
	sem_wait(philo->mutex);
}

int main(int argc, char **argv)
{
	t_var	var;

	get_struct_var(&var);
	parse_data(argc, argv);
	if (var.error == 1)
		return (1);
	else 
		phil_init_start();
	return (0);
}
