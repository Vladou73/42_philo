/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:46:38 by vnafissi          #+#    #+#             */
/*   Updated: 2022/04/04 11:11:45 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int	ft_dead_loop_check(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->nb_philos)
	{
		pthread_mutex_lock(&game->philos[i].lock_philo);
		if (ft_gettimeofday_ms() - game->philos[i].last_meal
			>= game->time_to_die && game->dead_philo == 0)
		{
			pthread_mutex_unlock(&game->philos[i].lock_philo);
			pthread_mutex_lock(&game->lock_death);
			game->dead_philo = 1;
			printf("%ld %d died\n", ft_gettime_since_game_start(
					game->start_time), game->philos[i].index);
			pthread_mutex_unlock(&game->lock_death);
			return (1);
		}
		pthread_mutex_unlock(&game->philos[i].lock_philo);
		i++;
		usleep(300);
	}
	return (0);
}

int	ft_dead_routine(t_game *game)
{
	usleep(100);
	while (1)
	{
		if (ft_all_philos_have_eaten_enough(game))
			return (0);
		if (ft_dead_loop_check(game))
			return (1);
	}
	return (0);
}

int	is_a_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->lock_death);
	if (philo->game->dead_philo)
	{
		pthread_mutex_unlock(&philo->game->lock_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->game->lock_death);
	return (0);
}

int	ft_act(t_philo *philo)
{
	if (philo->index % 2 == 0)
		ft_start_eating(philo, philo->left_fork, philo->right_fork);
	else
		ft_start_eating(philo, philo->right_fork, philo->left_fork);
	if (philo->nb_times_eat >= philo->game->nb_times_philos_must_eat
		&& philo->game->nb_times_philos_must_eat >= 0)
		return (0);
	ft_start_sleeping(philo);
	ft_start_thinking(philo);
	usleep(50);
	return (1);
}

int	ft_routine(t_philo *philo)
{
	if (philo->game->nb_philos > 1)
	{
		if (philo->index % 2 == 0)
			usleep(4000);
		while (1)
		{
			if (is_a_philo_dead(philo))
				return (1);
			else
			{
				if (ft_act(philo) == 0)
					return (0);
			}
		}
	}
	else
		ft_printf(philo, "has taken a fork");
	return (0);
}
