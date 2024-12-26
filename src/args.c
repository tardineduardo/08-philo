/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 18:57:12 by eduribei          #+#    #+#             */
/*   Updated: 2024/12/25 19:12:28 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_validate_args(int argc, char *argv[], t_resources *r)
{
	//improve validations	
	if (argc != 5 && argc != 6)
	{
		ft_free_resources(r);
		printf("invalid arguments.\n");
		exit(1);
	}
	r->params = malloc(sizeof(t_params));
	if (!r->params)
	{
		printf("memory errorzzz.\n");		
		ft_free_resources(r);
		exit(2);
	}
	r->params->nphilos = ft_atoi(argv[1]);
	r->params->nforks = ft_atoi(argv[1]);
	r->params->tdie = ft_atoi(argv[2]);
	r->params->teat = ft_atoi(argv[3]);
	r->params->tsleep = ft_atoi(argv[4]);
	if (argc == 6)
		r->params->nmeals = ft_atoi(argv[5]);
	else
		r->params->nmeals = 0;		
	return ;
}
