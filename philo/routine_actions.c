/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:46:38 by vnafissi          #+#    #+#             */
/*   Updated: 2022/03/17 18:52:09 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void ft_start_eating(t_philo *philo)
{
	//int pthread_mutex_lock(pthread_mutex_t *mutex);
	pthread_mutex_lock(&philo->game->forks[philo->left_fork]); //in case lock fails, need to check
	printf("%ld %d has taken a fork\n", ft_gettimeofday_ms(), philo->index);
	pthread_mutex_lock(&philo->game->forks[philo->right_fork]); //in case lock fails, need to check
	printf("%ld %d has taken a fork\n", ft_gettimeofday_ms(), philo->index);
	
	pthread_mutex_lock(&philo->lock_philo);
	philo->status = 0;
	printf("%ld %d is eating\n", ft_gettimeofday_ms(), philo->index);

	usleep(philo->game->time_to_eat * 1000);
	philo->nb_times_eat++;
	printf("%d ate %d times\n", philo->index, philo->nb_times_eat);
	pthread_mutex_unlock(&philo->lock_philo);
	
	philo->last_time_ate = ft_gettimeofday_ms();
	pthread_mutex_unlock(&philo->game->forks[philo->left_fork]); //in case unlock fails, need to check
	pthread_mutex_unlock(&philo->game->forks[philo->right_fork]); //in case unlock fails, need to check
}

void ft_start_sleeping(t_philo *philo)
{
	printf("%ld %d is sleeping\n", ft_gettimeofday_ms(), philo->index);
	philo->status = 1;
	usleep(philo->game->time_to_sleep * 1000);
}

void ft_start_thinking(t_philo *philo)
{
	printf("%ld %d is thinking\n", ft_gettimeofday_ms(), philo->index);
	philo->status = 2;
	usleep(philo->game->time_to_think * 1000);
}

void	*ft_dead_routine(void *arg)
{
	int		i;
	usleep(200);
	
	//POURQUOI CA NE FONCTIONNE PAS AVEC LA STRUCTURE game DIRECTEMENT ?
	//game = *(t_game*)arg;
	t_game	game;
	game = *(((t_philo*)arg)->game);
	
	//The condition to go out of this while loop is if a philo is dead ==> put in place the other thread which tests indefinitely if a philo is dead
	while (1)
	{
		i = 0;
		while (i < game.nb_philos)
		{
			pthread_mutex_lock(&game.philos[i].lock_philo);
			printf("%d ate for the last time : %ld\n", game.philos[i].index, game.philos[i].last_time_ate);
			pthread_mutex_unlock(&game.philos[i].lock_philo);
			i++;
		}
		usleep(10000 * 1000);
	}
	return (arg);
}


void	*ft_routine(void *arg)
{
	t_philo philo;

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
		printf("last time philo %d ate=%ld\n",philo.index, philo.last_time_ate);
		
		usleep(1);
	}
	return (arg);
}
