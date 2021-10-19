#include "philo_three.h"

void	assing_data(t_var	*var, char **argv, int argc)
{
	var->num_phil = ft_atoi(argv[1]);
	if (var->num_phil > 200)
	{
		printf("Check number of philosopher is more than 200!\n");
		var->error = 1;
		return ;
	}
	var->time_die = ft_atoi(argv[2]);
	var->time_eat = ft_atoi(argv[3]);
	var->time_sleep = ft_atoi(argv[4]);
	if (var->time_die < 60 || var->time_eat < 60 || var->time_sleep < 60)
	{
		printf("Time is under 60 ms!\n");
		var->error = 1;
		return ;
	}
	if (argc == 6)
		var->count = ft_atoi(argv[5]);
	else
		var->count = -1;
}

void	check_isnum(char **argv, t_var *var)
{
	int		i;
	int		j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isnum(argv[i][j]))
			{
				printf("not a valid format!\n");
				var->error = 1;
				return ;
			}
		}
	}
}

void	parse_data(int argc, char **argv)
{
	t_var	*var;
	int		i;

	i = 0;
	var = get_struct_var(NULL);
	var->error = 0;
	if (argc < 5 || argc > 6)
	{
		printf("number of arguments failed!\n");
		var->error = 1;
	}
	else
	{
		check_isnum(argv, var);
		if (var->error)
			return ;
		assing_data(var, argv, argc);
	}
}
