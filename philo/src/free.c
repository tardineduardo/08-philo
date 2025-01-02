/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:22:32 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/02 20:36:30 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	ft_destroy_mutexes(t_main *main)
{
	size_t	a;

	if (main->forks)
	{
		a = 0;
		while (a < main->params->nb_forks + 1)
			pthread_mutex_destroy(&main->forks[a++]);
		free(main->forks);
	}
	pthread_mutex_destroy(&main->stop_mutex);
	pthread_mutex_destroy(&main->print_mutex);
	pthread_mutex_destroy(&main->time_mutex);	
	return ;
}

void	ft_free_resources(t_main *main)
{
	if (!main)
		return ;
	if (main->th)
		free(main->th);
	if (main->ph)
		free(main->ph);
	if (main->params)
		free(main->params);
	return ;
}
