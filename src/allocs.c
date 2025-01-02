/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:07:21 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/01 23:14:54 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_alloc_resources(t_resources *main)
{
	t_params	*params;

	params = main->params;
	params->must_stop = false;
	gettimeofday(&params->start_time, NULL);
	main->forks = calloc(params->nb_forks + 1, sizeof(pthread_mutex_t));
	main->th = calloc(params->nb_philos, sizeof(pthread_t));
	main->philo = calloc(params->nb_philos, sizeof(t_philos));
	if (!main->forks || !main->th || !main->philo)
	{
		printf("malloc error.\n");
		ft_free_resources(main);
		exit(1);
	}
	return ;
}
