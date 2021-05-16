#include "philo_one.h"

t_var *get_struct_var(t_var *ptr)
{
    static t_var *tmp;

    if (ptr)
        tmp = ptr;
    return (tmp);
}

int	get_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	aff_msg(t_philo *ph, int status)
{
	t_var *var = get_struct_var(NULL);

	pthread_mutex_lock(&var->msg_mutex);
	ft_putnbr_fd(get_time() - var->start, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(ph->index + 1, 1);
	ft_putstr_fd(" ", 1);
	if (status == FORK)
		ft_putstr_fd("has taken a fork\n", 1);
	else if (status == EAT)
		ft_putstr_fd("is eating\n", 1);
	else if (status == SLEEP)
		ft_putstr_fd("is sleeping\n", 1);
	else if (status == THINK)
		ft_putstr_fd("is thinking\n", 1);
	pthread_mutex_unlock(&var->msg_mutex);
}

int	take_forks(t_philo *ph)
{
	t_var *var = get_struct_var(NULL);
	if (var->is_died)
	{
		pthread_mutex_lock(&var->forks_mutex[ph->ph_left]);
		aff_msg(ph, FORK);
		pthread_mutex_lock(&var->forks_mutex[ph->ph_right]);
		aff_msg(ph, FORK);
		return (1);
	}
	return (0);
}

int	eat_phil(t_philo *ph)
{
	int	t_eat;

	t_var *var = get_struct_var(NULL);
	t_eat = var->time_eat * 1000;
	if (var->is_died)
	{
		aff_msg(ph, EAT);
		// ph->limit = get_time() + var->time_die;
		usleep(t_eat);
		return (1);
	}
	return (0);
}

int	release_forks(t_philo *ph)
{
	t_var *var = get_struct_var(NULL);
	if (var->is_died)
	{
		pthread_mutex_unlock(&var->forks_mutex[ph->ph_left]);
		pthread_mutex_unlock(&var->forks_mutex[ph->ph_right]);
		return (1);
	}
	return (0);
}

int	sleep_phil(t_philo *ph)
{
	int t_sleep;

	t_var *var = get_struct_var(NULL);
	t_sleep = var->time_sleep * 1000;
	if (var->is_died)
	{
		aff_msg(ph, SLEEP);
		usleep(t_sleep);
		return (1);
	}
	return (0);
}

void	*routine_phil(void	*data)
{
	t_philo *ph;

	ph = data;
	t_var *var = get_struct_var(NULL);
	// ph->limit = get_time() + var->time_die;
	while (var->is_died)
	{
		if (!take_forks(ph))
			return (NULL);
		if (!eat_phil(ph))
			return (NULL);
		if (!release_forks(ph))
			return (NULL);
		if (!sleep_phil(ph))
			return (NULL);
		aff_msg(ph, THINK);
	}
	
	return (NULL);
}

void	phil_init_start()
{
	t_philo	*philo;
	int		i;

	t_var *var = get_struct_var(NULL);
	philo = malloc(sizeof(t_philo) * var->num_phil);
	var->forks_mutex = malloc(sizeof(pthread_mutex_t) * var->num_phil);
	pthread_mutex_init(&var->msg_mutex, NULL);
	i = -1;
	while (++i < var->num_phil)
	{
		pthread_mutex_init(&var->forks_mutex[i], NULL);
		philo[i].index = i;
		philo[i].ph_left = i;
		philo[i].ph_right = (i + 1) % var->num_phil;
	}
	var->is_died = 1;
	//start circle philosopher
	i = -1;
	var->start = get_time();
	while (++i < var->num_phil)
	{
		pthread_create(&philo[i].tid, NULL, routine_phil, &philo[i]);
		pthread_detach(philo[i].tid);
	}
}	

int main(int argc, char **argv)
{
	t_var	var;
	int 	i;
	int		j;

	i = 0;
	get_struct_var(&var);
	if (argc < 5 || argc > 6)
		ft_putstr_fd("number of arguments failed!\n", 2);
	else
	{
		while (argv[++i])
		{
			j = -1;
			while (argv[i][++j])
			{
				if (!ft_isnum(argv[i][j]))
				{
					ft_putstr_fd("not a valid format!\n", 2);
					return (1);
				}
			}
		}
		var.num_phil = ft_atoi(argv[1]);
		var.time_die = ft_atoi(argv[2]);
		var.time_eat = ft_atoi(argv[3]);
		var.time_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			var.count = ft_atoi(argv[5]);
		//initial each philosopher
		phil_init_start();
		while (var.is_died)
		{
			usleep(3000);
		}
	}
	return (0);
}
