#include "philo_three.h"

t_var	*get_struct_var(t_var *ptr)
{
	static t_var	*tmp;

	if (ptr)
		tmp = ptr;
	return (tmp);
}

void	func_lock(t_var *var)
{
	sem_wait(var->msg_mutex);
	printf("sumilation stoped\n");
	sem_post(var->mutex);
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
		sem_wait(var->eat);
		all_philo_eat++;
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
	sem_wait(var->mutex);
	if (philo->eat_count > 0)
	{
		pthread_create(&philo->tid_eat, NULL, check_eat_count, philo);
		pthread_detach(philo->tid_eat);
	}
	while (++i < var->num_phil)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			routine(&philo[i]);
			exit (0);
		}
		usleep(100);
	}
	sem_wait(var->mutex);
	clear(var, philo);
}

int	main(int argc, char **argv)
{
	t_var	*var;

	var = (t_var *)malloc(sizeof(t_var));
	get_struct_var(var);
	parse_data(argc, argv);
	if (var->error == 1)
		return (1);
	else
		phil_init_start();
	free(var);
	return (0);
}
