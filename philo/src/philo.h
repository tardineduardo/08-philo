/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduribei <eduribei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:01:25 by eduribei          #+#    #+#             */
/*   Updated: 2025/01/03 13:27:26 by eduribei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>

typedef struct timeval	t_timeval;

typedef struct s_params
{
	size_t			nb_philos;
	size_t			nb_forks;
	size_t			tm_sleep;
	size_t			tm_die;
	size_t			tm_eat;
	size_t			nb_meals_to_eat;
	size_t			total_meals_ct;
	size_t			total_meals_goal;
	bool			thread_must_stop;
	t_timeval		start_time;
	pthread_mutex_t	*stop_mutex;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*time_mutex;
}	t_params;

typedef struct s_philos
{
	bool				is_detached;
	size_t				index;
	size_t				nb_meals_had;
	_Atomic size_t		tm_starv;
	t_timeval			tm_lastmeal;
	pthread_mutex_t		*fork1;
	pthread_mutex_t		*fork2;
	struct s_main		*main;
}	t_philos;

typedef struct s_main
{
	pthread_t		*th;
	pthread_t		monitor;
	pthread_t		join;
	pthread_mutex_t	*forks;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	time_mutex;
	t_philos		*ph;
	t_params		*params;
}	t_main;

//Validation
void	ft_validate_and_parse_args(int argc, char *argv[], t_main *main);
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
int		ft_isspace(int c);

//Inits
void	ft_init_main(t_main *main);
void	ft_init_threads(t_main *main);
void	ft_init_mutexes(t_main *main);
void	ft_alloc_resources(t_main *main);

//Philosopher
void	*ft_philo(void *args);

//Actions
bool	ft_grab_fork_1(t_philos *philo, t_params *params);
bool	ft_grab_fork_2(t_philos *philo, t_params *params);
bool	ft_eating(t_philos *philo, t_params *params);
bool	ft_sleeping(t_philos *philo, t_params *params);
bool	ft_thinking(t_philos *philo, t_params *params);

//Monitor
void	*ft_stop_monitor(void *arg);
bool	ft_thread_must_stop(t_params *params);

//Exiting
void	ft_free_resources(t_main *main);

//Error
void	ft_error(char *message, int errnum, t_main *main);

//Time
void	ft_get_time(t_timeval *timeval, pthread_mutex_t *mutex);
size_t	ft_t_delta_ms(t_timeval start, t_timeval end);
size_t	ft_t_delta_us(t_timeval start, t_timeval end);

# define RST	"\033[0m"
# define GREEN	"\033[32m"
# define RED	"\033[31m"

#endif
