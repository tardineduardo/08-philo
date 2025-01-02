/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:57:12 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/01 23:15:37 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_validate_args(int argc, char *argv[], t_resources *r)
{
	if (argc != 5 && argc != 6)
		ft_error("invalid arguments.\n", r);
	r->params = malloc(sizeof(t_params));
	if (!r->params)
		ft_error("malloc failed.\n", r);
	r->params->nb_philos = ft_atoi(argv[1]);
	r->params->nb_forks = r->params->nb_philos;
	r->params->time_to_die = ft_atoi(argv[2]) * 1000;
	r->params->time_eating = ft_atoi(argv[3]) * 1000;
	r->params->time_sleeping = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
	{
		r->params->number_of_meals_to_eat = ft_atoi(argv[5]);
		r->params->total_meals_goal = ft_atoi(argv[5]) * ft_atoi(argv[1]);
		r->params->total_meals_count = 0;
	}
	else
	{
		r->params->number_of_meals_to_eat = -1;
		r->params->total_meals_goal = -1;
		r->params->total_meals_count = 0;
	}
	return ;
}
