#include "philo_one.h"

unsigned	long	get_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	aff_msg(t_var *var, int status)
{
	pthread_mutex_lock(&var->msg_mutex);
	ft_putnbr_fd(get_time() - var->t_start, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(var->index + 1, 1);
	ft_putstr_fd(" ", 1);
	if (status == FORK)
		ft_putstr_fd("has taken a fork\n", 1);
	else if (status == EAT)
		ft_putstr_fd("is eating\n", 1);
	else if (status == SLEEP)
		ft_putstr_fd("is sleeping\n", 1);
	else if (status == THINK)
		ft_putstr_fd("is thinking\n", 1);
	if (status != DIED)
		pthread_mutex_unlock(&var->msg_mutex);
}

int	take_forks(t_var *var)
{
	if (var->is_died)
	{
		pthread_mutex_lock(&var->forks_mutex[var->ph_left]);
		aff_msg(var, FORK);
		if (var->is_died)
		{
			pthread_mutex_lock(&var->forks_mutex[var->ph_right]);
			aff_msg(var, FORK);
			return (1);
		}
	}
	return (0);
}

int	eat_phil(t_var *var)
{
	int	t_eat;

	t_eat = var->time_eat * 1000;
	if (var->is_died)
	{
		aff_msg(var, EAT);
		usleep(t_eat);
		return (1);
	}
	return (0);
}

int	release_forks(t_var *var)
{
	if (var->is_died)
	{
		pthread_mutex_unlock(&var->forks_mutex[var->ph_left]);
		pthread_mutex_unlock(&var->forks_mutex[var->ph_right]);
		return (1);
	}
	return (0);
}

int	sleep_phil(t_var *var)
{
	int t_sleep;

	t_sleep = var->time_sleep * 1000;
	if (var->is_died)
	{
		aff_msg(var, SLEEP);
		usleep(t_sleep);
		return (1);
	}
	return (0);
}

void	*routine_phil(void	*data)
{
	t_var *var;
	
	var = data;
	while (var->is_died)
	{
		if (!take_forks(var))
			return (NULL);
		if (!eat_phil(var))
			return (NULL);
		if (!release_forks(var))
			return (NULL);
		if (!sleep_phil(var))
			return (NULL);
		aff_msg(var, THINK);
		usleep(100);
	}
	
	return (NULL);
}

void	phil_init(t_var *var)
{
	int	i;

	i = -1;
	//initial mutex the each philosopher
	var->forks_mutex = malloc(sizeof(pthread_mutex_t) * var->num_phil);
	pthread_mutex_init(&var->msg_mutex, NULL);
	while (++i < var->num_phil)
		pthread_mutex_init(&var->forks_mutex[i], NULL);
	i = -1;
	while (++i < var->num_phil)
	{
		var[i].index = i;
		var[i].eat_count = 0;
		var[i].ph_left = i;
		var[i].ph_right = (i + 1) % var->num_phil;
	}
	var->is_died = 1;

	//start circle philosopher
	var->t_start =  get_time();
	i = -1;
	while (++i < var->num_phil)
	{
		pthread_create(&var[i].tid, NULL, routine_phil, &var[i]);
		pthread_detach(var[i].tid);
		usleep(1000);
	}
}

int main(int argc, char **argv)
{
	t_var	var;
	int 	i;
	int		j;

	i = 0;
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
		phil_init(&var);
	}
	return (0);
}
