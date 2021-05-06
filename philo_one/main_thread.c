#include "philo_one.h"

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

		printf("num_phil:%d | time_die:%d | time_eat:%d | time_sleep:%d\n", var.num_phil, var.time_die, var.time_eat, var.time_sleep);
		
	}
	
	return (0);
}
