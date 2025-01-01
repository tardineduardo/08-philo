/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:01:18 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/01 18:46:53 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_stop(t_philos *philo, t_params *params)
{
	size_t	timedelta;
	size_t	t_since_last_meal;

	pthread_mutex_lock(params->stop_mutex);
	if (params->is_someone_dead)
	{
		pthread_mutex_unlock(params->stop_mutex);
		return (true);
	}
	gettimeofday(&philo->curr_time, NULL);
	t_since_last_meal = ft_t_delta_us(philo->t_of_last_meal, philo->curr_time);
	if (t_since_last_meal >= params->time_to_die)
	{
		params->is_someone_dead = true;
		gettimeofday(&philo->curr_time, NULL);
		timedelta = ft_t_delta_ms(params->start_time, philo->curr_time);
		pthread_mutex_lock(params->print_mutex);
		printf("%li %li died\n", timedelta, philo->index + 1);
		pthread_mutex_unlock(params->print_mutex);
		pthread_mutex_unlock(params->stop_mutex);
		return (true);
	}
	pthread_mutex_unlock(params->stop_mutex);
	return (false);
}

void	*ft_philo(void *args)
{
	t_philos	*philo;
	t_params	*params;

	philo = (t_philos *)args;
	params = philo->main->params;
	while (1)
	{
		if (!philo_grab_fork_1(philo, params))
			return (NULL);
		if (!philo_grab_fork_2(philo, params))
			return (NULL);
		if (!philo_eating(philo, params))
			return (NULL);
		if (!philo_sleeping(philo, params))
			return (NULL);
		if (!philo_thinking(philo, params))
			return (NULL);
	}
	printf(BLUE "philo %li is done.\n" RESET, philo->index);
	return (NULL);
}

void	ft_join_threads(t_resources *main)
{
	int	i;

	i = 0;
	while (i < main->params->number_of_philos)
	{
		pthread_join(main->th[i], NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_resources		*main;

	main = malloc(sizeof(t_resources));
	if (!main)
		ft_error("malloc failed.\n", main);
	ft_validate_args(argc, argv, main);
	ft_alloc_resources(main);
	ft_init_mutexes(main);
	ft_init_threads(main);
	ft_join_threads(main);
	ft_free_resources(main);
}
