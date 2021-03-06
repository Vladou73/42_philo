/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:30:35 by vnafissi          #+#    #+#             */
/*   Updated: 2022/03/31 17:15:31 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int	ft_start_eating(t_philo *philo, int first_fork, int second_fork)
{
	pthread_mutex_lock(&philo->game->forks[first_fork]);
	ft_printf(philo, "has taken a fork");
	pthread_mutex_lock(&philo->game->forks[second_fork]);
	ft_printf(philo, "has taken a fork");
	ft_printf(philo, "is eating");
	pthread_mutex_lock(&philo->lock_philo);
	philo->nb_times_eat++;
	philo->last_meal = ft_gettimeofday_ms();
	pthread_mutex_unlock(&philo->lock_philo);
	ft_usleep(philo->game->time_to_eat, philo);
	pthread_mutex_unlock(&philo->game->forks[second_fork]);
	pthread_mutex_unlock(&philo->game->forks[first_fork]);
	return (0);
}

int	ft_start_sleeping(t_philo *philo)
{
	ft_printf(philo, "is sleeping");
	ft_usleep(philo->game->time_to_sleep, philo);
	return (0);
}

int	ft_start_thinking(t_philo *philo)
{
	ft_printf(philo, "is thinking");
	ft_usleep((philo->game->time_to_eat - philo->game->time_to_sleep)
		+ 1, philo);
	return (0);
}
