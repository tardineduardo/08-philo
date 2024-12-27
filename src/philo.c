/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:01:18 by eduribei          #+#    #+#             */
/*   Updated: 2024/12/25 22:37:42 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	eat(t_resources *r)
{

}

void	thsleep(t_resources *r)
{


}

void	think(void)
{

}



void	*ft_philosopher(void *args)
{
	t_philo	*data;

	data = (t_philo *)args;
	printf("Hello from philosopher %li.\n", data->index);
}

void	*ft_init_threads(t_resources *r)
{
	int	i;

	i = 0;

	while (i < r->params->nphilos)
	{
		r->philo[i].index = i;
		r->philo[i].detached = false;
		r->philo->r = r;
		pthread_create(&r->th[i], NULL, &ft_philosopher, (void *)&r->philo[i]);
		i++;
	}
	return ;
}

void	*ft_join_threads(t_resources *r)
{
	int	i;

	i = 0;
	while (i < r->params->nphilos)
	{
		if (!r->philo[i].detached)
			pthread_join(r->th[i], NULL);
		i++;
	}
}



int	main(int argc, char *argv[])
{
	t_resources		*r;

	r = malloc(sizeof(t_resources));
	if (!r)
		ft_error("malloc failed.\n", r);
	ft_validate_args(argc, argv, r);
	ft_alloc_resources(r);
	ft_init_threads(r);
	ft_join_threads(r);
	ft_free_resources(r);
}
