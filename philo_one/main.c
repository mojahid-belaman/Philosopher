#include "philo_one.h"

t_var	*get_struct_var(t_var *ptr)
{
	static t_var	*tmp;

	if (ptr)
		tmp = ptr;
	return (tmp);
}

void	func_lock(t_var *var)
{
	pthread_mutex_lock(&var->msg_mutex);
	printf("sumilation stoped\n");
	pthread_mutex_unlock(&var->mutex);
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
	func_lock(var);
	return (NULL);
}

void	phil_init_start(void)
{
	t_philo	*philo;
	t_var	*var;
	int		i;

	var = get_struct_var(NULL);
	philo = init_philo_mutex();
	i = -1;
	pthread_mutex_lock(&var->mutex);
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
	clear_destroy_ph(philo);
	pthread_mutex_lock(&var->mutex);
}

int	main(int argc, char **argv)
{
	t_var	var;

	get_struct_var(&var);
	parse_data(argc, argv);
	if (var.error)
		return (1);
	else
		phil_init_start();
	return (0);
}
