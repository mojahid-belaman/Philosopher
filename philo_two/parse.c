#include "philo_two.h"

void    parse_data(int argc, char **argv)
{
    t_var   *var;
    int 	i;
	int		j;

	i = 0;
    var = get_struct_var(NULL);
    if (argc < 5 || argc > 6)
    {
		printf("number of arguments failed!\n");
        var->error = 1;
    }
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
					var->error = 1;
				}
			}
		}
		var->num_phil = ft_atoi(argv[1]);
		var->time_die = ft_atoi(argv[2]);
		var->time_eat = ft_atoi(argv[3]);
		var->time_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			var->count = ft_atoi(argv[5]);
		else
			var->count = -1;
    }
}