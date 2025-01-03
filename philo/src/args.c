/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:57:12 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/03 12:45:34 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_only_digits_and_space(int argc, char *argv[], t_main *main)
{
	int	a;
	int	b;

	a = 1;
	while (a < argc)
	{
		b = 0;
		while (argv[a][b] != '\0')
		{
			if (!ft_isdigit(argv[a][b]))
				ft_error("Invalid arguments.\n", EINVAL, main);
			b++;
		}
		a++;
	}
	return ;
}

void	ft_validate_and_parse_args(int argc, char *argv[], t_main *main)
{
	if (argc != 5 && argc != 6)
		ft_error("invalid arguments.\n", EINVAL, main);
	main->params = malloc(sizeof(t_params));
	if (!main->params)
		ft_error("malloc failed.\n", errno, main);
	ft_only_digits_and_space(argc, argv, main);
	main->params->nb_philos = ft_atoi(argv[1]);
	main->params->nb_forks = main->params->nb_philos;
	main->params->tm_die = ft_atoi(argv[2]) * 1000;
	main->params->tm_eat = ft_atoi(argv[3]) * 1000;
	main->params->tm_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
	{
		main->params->nb_meals_to_eat = ft_atoi(argv[5]);
		main->params->total_meals_goal = ft_atoi(argv[5]) * ft_atoi(argv[1]);
		main->params->total_meals_ct = 0;
	}
	else
	{
		main->params->nb_meals_to_eat = -1;
		main->params->total_meals_goal = -1;
		main->params->total_meals_ct = 0;
	}
	return ;
}
