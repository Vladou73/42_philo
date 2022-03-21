/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:46:38 by vnafissi          #+#    #+#             */
/*   Updated: 2022/03/21 15:10:10 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void ft_start_eating(t_philo *philo, int first_fork, int second_fork)
{
	//int pthread_mutex_lock(pthread_mutex_t *mutex);
	pthread_mutex_lock(&philo->game->forks[first_fork]); //in case lock fails, need to check
	printf("%ld %d has taken a fork\n", ft_gettime_since_game_start(philo->game->start_time), philo->index);
	pthread_mutex_lock(&philo->game->forks[second_fork]); //in case lock fails, need to check
	printf("%ld %d has taken a fork\n", ft_gettime_since_game_start(philo->game->start_time), philo->index);
	
	pthread_mutex_lock(&philo->lock_philo);
	printf("%ld %d is eating\n", ft_gettime_since_game_start(philo->game->start_time), philo->index);
	usleep(philo->game->time_to_eat * 1000);
	philo->nb_times_eat++;
	philo->last_time_ate = ft_gettime_since_game_start(philo->game->start_time);
//	printf("%d ate %d times\n", philo->index, philo->nb_times_eat);
	pthread_mutex_unlock(&philo->lock_philo);
	
	pthread_mutex_unlock(&philo->game->forks[first_fork]); //in case unlock fails, need to check
	pthread_mutex_unlock(&philo->game->forks[second_fork]); //in case unlock fails, need to check
}

void ft_start_sleeping(t_philo *philo)
{
	printf("%ld %d is sleeping\n", ft_gettime_since_game_start(philo->game->start_time), philo->index);
	usleep(philo->game->time_to_sleep * 1000);
}

void ft_start_thinking(t_philo *philo)
{
	printf("%ld %d is thinking\n", ft_gettime_since_game_start(philo->game->start_time), philo->index);
}

int	ft_dead_routine(t_game *game)
{
	int		i;
	usleep(20);
	
	//The condition to go out of this while loop is if a philo is dead ==> put in place the other thread which tests indefinitely if a philo is dead
	while (1)
	{
		i = 0;
		while (i < game->nb_philos)
		{
			pthread_mutex_lock(&game->philos[i].lock_philo);
			printf("philo %d // time_to_die=%ld // ate_for_the_last_time=%ld\n", game->philos[i].index, game->time_to_die, game->philos[i].last_time_ate);
			printf("time_since_game_started=%ld\n", game->philos[i].last_time_ate + ft_gettime_since_game_start(game->start_time));
			pthread_mutex_unlock(&game->philos[i].lock_philo);
			i++;
		}
		usleep(500);
	}
	return (0);
}

//5000  
//time to die 7000
//



int	ft_routine(t_philo *philo)
{
	//The condition to go out of this while loop is if a philo is dead ==> put in place the other thread which tests indefinitely if a philo is dead
	while (1)
	{
		pthread_mutex_lock(&philo->lock_philo);
		if (philo->index % 2 == 0)
		{
			pthread_mutex_unlock(&philo->lock_philo);
			ft_start_eating(philo, philo->left_fork, philo->right_fork); //2nd argument is the 1st fork to block
		}
		else
		{
			pthread_mutex_unlock(&philo->lock_philo);
			ft_start_eating(philo, philo->right_fork, philo->left_fork);	
		}
		ft_start_sleeping(philo);
		ft_start_thinking(philo);
		usleep(1);
	}
	return (0);
}
