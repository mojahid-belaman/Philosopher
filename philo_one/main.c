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

void	take_forks(t_philo *ph)
{
	t_var *var = get_struct_var(NULL);

	if (ph->is_dead)
	{
		pthread_mutex_lock(&var->forks_mutex[ph->ph_left]);
		aff_msg(ph, FORK);
		pthread_mutex_lock(&var->forks_mutex[ph->ph_right]);
		aff_msg(ph, FORK);
	}
}

void	eat_phil(t_philo *ph)
{
	int	t_eat;

	t_var *var = get_struct_var(NULL);
	t_eat = var->time_eat * 1000;
	if (ph->is_dead)
	{
		aff_msg(ph, EAT);
		if (ph->eat_count != -1)
			ph->eat_count--;
		ph->t_start = get_time();
		ph->t_limit = ph->t_start + var->time_die;
		usleep(t_eat);
	}
}

void	release_forks(t_philo *ph)
{
	t_var *var = get_struct_var(NULL);

	pthread_mutex_unlock(&var->forks_mutex[ph->ph_left]);
	pthread_mutex_unlock(&var->forks_mutex[ph->ph_right]);
}

void	sleep_phil(t_philo *ph)
{
	int t_sleep;
	t_var *var = get_struct_var(NULL);
	if (ph->is_dead)
	{
		t_sleep = var->time_sleep * 1000;
		aff_msg(ph, SLEEP);
		usleep(t_sleep);
	}
}

void	*check_eat_count(void *arg)
{
	t_philo *ph = (t_philo *)arg;
	t_var	*var = get_struct_var(NULL);

	int i = 0;
	int all_philo_eat = 0;
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
	pthread_mutex_lock(&var->msg_mutex);
	printf("sumilation stoped\n");
	pthread_mutex_unlock(ph->mutex);
	return (NULL);
}

void	*check_die_phil(void	*data)
{
	t_philo	*ph;
	// t_var	*var = get_struct_var(NULL);

	ph = data;
	while (1)
	{
		pthread_mutex_lock(ph->die_mutex);
		if (get_time() > ph->t_limit)
		{
			aff_msg(ph, DIED);
			ph->is_dead = 0;
			pthread_mutex_unlock(ph->mutex);
			return (NULL);
		}
		pthread_mutex_unlock(ph->die_mutex);
	}
	return (NULL);
}

void	check_health_phil(t_philo *ph)
{
	// t_var *var = get_struct_var(NULL);

	if (ph->is_dead)
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
	while (1)
	{
		take_forks(ph);
		eat_phil(ph);
		release_forks(ph);
		if (ph->eat_count == 0)
		{
			ph->check_each_ph_eat = 1;
			break ;
		}
		sleep_phil(ph);
		aff_msg(ph, THINK);
		usleep(100);
	}
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
	pthread_mutex_lock(philo->mutex);
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
	pthread_mutex_lock(philo->mutex);
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
		{
			var.count = ft_atoi(argv[5]);
			var.c = var.count;
		}
		else
			var.count = -1;
		phil_init_start();
	}
	return (0);
}
