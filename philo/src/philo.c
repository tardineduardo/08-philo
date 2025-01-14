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

static void	ft_join_threads(t_main *main)
{
	size_t	i;

	i = 0;
	while (i < main->params->nb_philos)
	{
		pthread_join(main->th[i], NULL);
		i++;
	}
	pthread_join(main->monitor, NULL);
}

void	*ft_philo(void *args)
{
	t_philos	*ph;
	t_params	*params;

	ph = (t_philos *)args;
	params = ph->main->params;
	if (ph->index % 2 == 0)
		usleep(params->tm_eat / 2);
	else if (params->nb_philos % 2 == 1 && ph->index == params->nb_philos - 1)
		usleep(params->tm_eat * 3 / 4);
	while (1)
	{
		if (!ft_grab_fork_1(ph, params))
			return (NULL);
		if (!ft_grab_fork_2(ph, params))
			return (NULL);
		if (!ft_eating(ph, params))
			return (NULL);
		if (!ft_sleeping(ph, params))
			return (NULL);
		if (!ft_thinking(ph, params))
			return (NULL);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_main	*main;

	main = malloc(sizeof(t_main));
	if (!main)
		ft_error("malloc failed.\n", errno, main);
	ft_init_main(main);
	ft_validate_and_parse_args(argc, argv, main);
	ft_alloc_resources(main);
	ft_init_mutexes(main);
	ft_init_threads(main);
	ft_join_threads(main);
	ft_free_resources(main);
	return (0);
}
