/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:22:32 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/02 21:21:09 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_resources(t_main *main)
{
	size_t	a;

	a = 0;
	if (!main)
		return ;
	if (main->th)
		free(main->th);
	if (main->ph)
		free(main->ph);
	if (main->forks)
	{
		while (a < main->params->nb_forks)
			pthread_mutex_destroy(&main->forks[a++]);
		free(main->forks);
		pthread_mutex_destroy(&main->stop_mutex);
		pthread_mutex_destroy(&main->print_mutex);
		pthread_mutex_destroy(&main->time_mutex);
	}
	if (main->params)
		free(main->params);
	free(main);
	return ;
}
