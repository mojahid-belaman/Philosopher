#include "philo_one.h"

void	phil_init(t_var *var)
{
	int	i;

	i = -1;
	while (++i < var->num_phil)
	{
		
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
		phil_init(&var);		
	}
	
	return (0);
}
