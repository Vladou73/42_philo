/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:46:38 by vnafissi          #+#    #+#             */
/*   Updated: 2022/03/16 21:47:02 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void ft_start_eating(t_philo *philo)
{
	//int pthread_mutex_lock(pthread_mutex_t *mutex);
	pthread_mutex_lock(&philo->game->forks[philo->left_fork]); //in case lock fails, need to check
	pthread_mutex_lock(&philo->game->forks[philo->right_fork]); //in case lock fails, need to check

	gettimeofday(&philo->game->current_time, NULL);
	printf("%ld %d has taken a fork\n", philo->game->current_time.tv_sec * 1000, philo->index); //voir si il faut pas gérer autrement pour la précision des millisecondes

	philo->status = 0;

	gettimeofday(&philo->game->current_time, NULL);
	printf("%ld %d is eating\n", philo->game->current_time.tv_sec * 1000, philo->index);

	usleep(philo->game->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->game->forks[philo->left_fork]); //in case unlock fails, need to check
	pthread_mutex_unlock(&philo->game->forks[philo->right_fork]); //in case unlock fails, need to check
}

void ft_start_sleeping(t_philo *philo)
{
	gettimeofday(&philo->game->current_time, NULL);
	printf("%ld %d is sleeping\n", philo->game->current_time.tv_sec * 1000, philo->index);
	philo->status = 1;
	usleep(philo->game->time_to_sleep * 1000);
}

void ft_start_thinking(t_philo *philo)
{
	gettimeofday(&philo->game->current_time, NULL);
	printf("%ld %d is thinking\n", philo->game->current_time.tv_sec * 1000, philo->index);
	philo->status = 2;
	usleep(philo->game->time_to_think * 1000);
}

void	*ft_routine(void *arg)
{
	t_philo philo;


	//Need to put in place a while loop.
	//The condition to go out of this while loop is if a philo is dead ==> put in place the other thread which tests indefinitely if a philo is dead

	philo = *(t_philo*)arg;
	while (1)
	{
		if (philo.status == 2)
		{
			ft_start_eating(&philo);
		}
		else if (philo.status == 0)
		{
			ft_start_sleeping(&philo);
		}
		else if (philo.status == 1)
		{
			ft_start_thinking(&philo);
		}
	}
	return (arg);
}
