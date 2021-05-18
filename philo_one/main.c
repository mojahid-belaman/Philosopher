#include "philo_one.h"

t_var *get_struct_var(t_var *ptr)
{
    static t_var *tmp;

    if (ptr)
        tmp = ptr;
    return (tmp);
}

unsigned int	get_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	aff_msg(t_philo *ph, int status)
{
	t_var *var = get_struct_var(NULL);

	pthread_mutex_lock(&var->msg_mutex);
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
		pthread_mutex_unlock(&var->msg_mutex);
}

int	take_forks(t_philo *ph)
{
	t_var *var = get_struct_var(NULL);
	if (var->is_dead)
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
	if (var->is_dead)
	{
		// ph->check_eat = 1;
		aff_msg(ph, EAT);
		ph->t_start = get_time();
		ph->t_limit = ph->t_start + var->time_die;
		// ph->check_eat = 0;
		usleep(t_eat);
		return (1);
	}
	// pthread_mutex_unlock(ph->ph_mutex);
	return (0);
}

int	release_forks(t_philo *ph)
{
	t_var *var = get_struct_var(NULL);
	if (var->is_dead)
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
	if (var->is_dead)
	{
		aff_msg(ph, SLEEP);
		usleep(t_sleep);
		return (1);
	}
	return (0);
}

void	*check_die_phil(void	*data)
{
	t_philo	*ph;
	t_var	*var = get_struct_var(NULL);

	ph = data;
	while (var->is_dead)
	{
		pthread_mutex_lock(ph->die_mutex);
		if (get_time() > ph->t_limit)
		{
			aff_msg(ph, DIED);
			var->is_dead = 0;
			return (NULL);
		}
		pthread_mutex_unlock(ph->die_mutex);
	}
	return (NULL);
}

void	check_health_phil(t_philo *ph)
{
	t_var *var = get_struct_var(NULL);

	if (var->is_dead)
	{
		pthread_create(&ph->tid_health, NULL, check_die_phil, ph);
		pthread_detach(ph->tid_health);
	}
}

void	*routine_phil(void	*data)
{
	t_philo *ph;
	t_var *var = get_struct_var(NULL);

	ph = data;
	ph->t_limit = ph->t_start + var->time_die;
	check_health_phil(ph);
	while (var->is_dead)
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
	t_var *var = get_struct_var(NULL);
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * var->num_phil);
	philo->die_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	var->forks_mutex = malloc(sizeof(pthread_mutex_t) * var->num_phil);
	pthread_mutex_init(&var->msg_mutex, NULL);
	pthread_mutex_init(philo->die_mutex, NULL);
	i = -1;
	while (++i < var->num_phil)
	{
		pthread_mutex_init(&var->forks_mutex[i], NULL);
		philo[i].index = i;
		philo[i].ph_left = i;
		philo[i].ph_right = (i + 1) % var->num_phil;
		philo[i].t_start = get_time();
		philo[i].die_mutex = philo->die_mutex;
		philo[i].eat_count = 0;
	}
	var->is_dead = 1;
	var->start = get_time();
	//start circle philosopher
	i = -1;
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
		printf("number of arguments failed!\n");
	else
	{
		while (argv[++i])
		{
			j = -1;
			while (argv[i][++j])
			{
				if (!ft_isnum(argv[i][j]))
				{
					printf("not a valid format!\n");
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
		//initial each ph   ilosopher
		phil_init_start();
		while (var.is_dead)
			;
	}
	return (0);
}
