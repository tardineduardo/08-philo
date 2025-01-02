/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:57:12 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/02 12:07:09 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_validate_args(int argc, char *argv[], t_main *r)
{
	if (argc != 5 && argc != 6)
		ft_error("invalid arguments.\n", r);
	r->params = malloc(sizeof(t_params));
	if (!r->params)
		ft_error("malloc failed.\n", r);
	r->params->nb_philos = ft_atoi(argv[1]);
	r->params->nb_forks = r->params->nb_philos;
	r->params->tm_die = ft_atoi(argv[2]) * 1000;
	r->params->tm_eat = ft_atoi(argv[3]) * 1000;
	r->params->tm_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
	{
		r->params->nb_meals_to_eat = ft_atoi(argv[5]);
		r->params->total_meals_goal = ft_atoi(argv[5]) * ft_atoi(argv[1]);
		r->params->total_meals_ct = 0;
	}
	else
	{
		r->params->nb_meals_to_eat = -1;
		r->params->total_meals_goal = -1;
		r->params->total_meals_ct = 0;
	}
	return ;
}
