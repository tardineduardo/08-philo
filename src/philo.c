/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   philo.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: eduribei <eduribei@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/12/25 15:01:18 by eduribei		  #+#	#+#			 */
/*   Updated: 2025/01/01 21:10:22 by eduribei		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "philo.h"

bool	ft_stop(t_philos *philo, t_params *params)
{
	pthread_mutex_lock(params->stop_mutex);
	if (params->is_someone_dead)
	{
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
	if (philo->index % 2 == 1)
		usleep(params->time_eating / 2);
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
	t_resources	*main;

	main = malloc(sizeof(t_resources));
	if (!main)
		ft_error("malloc failed.\n", main);
	ft_validate_args(argc, argv, main);
	ft_alloc_resources(main);
	ft_init_mutexes(main);
	ft_init_threads(main);

	ft_join_threads(main);
	pthread_join(main->monitor, NULL);
	ft_free_resources(main);
	return (0);
}



	// Create monitor thread before philosopher threads
