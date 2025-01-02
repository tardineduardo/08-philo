/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 22:07:21 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/01 22:07:35 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_alloc_resources(t_resources *main)
{
	t_params	*params;

	params = main->params;
	params->is_someone_dead = false;
	gettimeofday(&params->start_time, NULL);
	main->forks = calloc(params->nb_of_forks + 1, sizeof(pthread_mutex_t));
	main->th = calloc(params->number_of_philos, sizeof(pthread_t));
	main->philo = calloc(params->number_of_philos, sizeof(t_philos));
	main->stop_mutex = calloc(1, sizeof(pthread_mutex_t));
	main->print_mutex = calloc(1, sizeof(pthread_mutex_t));
    main->meal_mutex = calloc(1, sizeof(pthread_mutex_t));
	if (!main->forks || !main->th || !main->philo || !main->print_mutex || !main->meal_mutex)
	{
		printf("malloc error.\n");
		ft_free_resources(main);
		exit(1);
	}
	return ;
}