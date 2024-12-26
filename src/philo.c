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

int	main(int argc, char *argv[])
{
	size_t			i;
	t_resources		*r;

	r = malloc(sizeof(t_resources));
	if (!r)
	{
		printf("malloc errorxxxx.\n");
		ft_free_resources(r);
		exit (1);
	}
	ft_validate_args(argc, argv, r);
	ft_alloc_resources(r);
	
	i = 0;
	while (i < r->params->nphilos)
	{
		r->philo[i].index = i;
		r->philo->r = r;
		pthread_create(&r->th[i], NULL, &ft_philosopher, (void *)&r->philo[i]);
		i++;
	}
	int j = 0;

	while (j < atoi(argv[1]))
	{
		pthread_join(r->th[j], NULL);
		j++;
	}

	ft_free_resources(r);
}
