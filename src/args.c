/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:57:12 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/01 17:42:55 by eduribei         ###   ########.fr       */
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
	r->params->number_of_philos = ft_atoi(argv[1]);
	r->params->nb_of_forks = ft_atoi(argv[1]);
	r->params->time_to_die = ft_atoi(argv[2]) * 1000;
	r->params->time_eating = ft_atoi(argv[3]) * 1000;
	r->params->time_sleeping = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		r->params->number_of_meals_to_eat = ft_atoi(argv[5]);
	else
		r->params->number_of_meals_to_eat = -1;
	return ;
}
