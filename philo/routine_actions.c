/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:46:38 by vnafissi          #+#    #+#             */
/*   Updated: 2022/03/21 19:22:33 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

int ft_start_eating(t_philo *philo, int first_fork, int second_fork)
{
	pthread_mutex_lock(&philo->game->forks[first_fork]); //in case lock fails, need to check
	printf("%ld %d has taken a fork\n", ft_gettime_since_game_start(philo->game->start_time), philo->index);
	pthread_mutex_lock(&philo->game->forks[second_fork]); //in case lock fails, need to check
	printf("%ld %d has taken a fork\n", ft_gettime_since_game_start(philo->game->start_time), philo->index);

	pthread_mutex_lock(&philo->lock_philo);
	printf("%ld %d is eating\n", ft_gettime_since_game_start(philo->game->start_time), philo->index);
	usleep(philo->game->time_to_eat * 1000);
	philo->nb_times_eat++;
	philo->last_meal = ft_gettimeofday_ms();
	pthread_mutex_unlock(&philo->lock_philo);
	
	pthread_mutex_unlock(&philo->game->forks[first_fork]); //in case unlock fails, need to check
	pthread_mutex_unlock(&philo->game->forks[second_fork]); //in case unlock fails, need to check
	return (0);
}

int	ft_start_sleeping(t_philo *philo)
{
	//if (is_a_philo_dead(philo))
	//	return (1);
	printf("%ld %d is sleeping\n", ft_gettime_since_game_start(philo->game->start_time), philo->index);
	usleep(philo->game->time_to_sleep * 1000);
	return (0);
}

int	ft_start_thinking(t_philo *philo)
{
	//if (is_a_philo_dead(philo))
	//	return (1);
	printf("%ld %d is thinking\n", ft_gettime_since_game_start(philo->game->start_time), philo->index);
	return (0);
}

int	ft_dead_routine(t_game *game)
{
	int		i;

	usleep(2);	
	while (1)
	{
		i = 0;
		while (i < game->nb_philos)
		{
			pthread_mutex_lock(&game->philos[i].lock_philo);
			if (ft_gettimeofday_ms() - game->philos[i].last_meal >= game->time_to_die && game->dead_philo == 0)
			{
				game->dead_philo = 1;
				printf("%ld %d died\n", ft_gettime_since_game_start(game->start_time), game->philos[i].index);
				pthread_mutex_unlock(&game->philos[i].lock_philo);
				return (1);
			}
			//printf("philo %d // time_to_die=%ld // ate_for_the_last_time=%ld\n", game->philos[i].index, game->time_to_die, game->philos[i].last_meal);
			//printf("time_since_last_meal=%ld\n", ft_gettimeofday_ms() - game->philos[i].last_meal);
			pthread_mutex_unlock(&game->philos[i].lock_philo);
			i++;
		}
		usleep(2);
	}
	return (0);
}

int	is_a_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock_philo);
	if (philo->game->dead_philo)
	{
		pthread_mutex_unlock(&philo->lock_philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock_philo);
	return (0);
}

int	ft_routine(t_philo *philo)
{
	//The condition to go out of this while loop is if a philo is dead ==> put in place the other thread which tests indefinitely if a philo is dead
	while (1)
	{
		//printf("dead_philo=%d\n", philo->game->dead_philo);
		if (is_a_philo_dead(philo))
			return (1);
		else
		{
			//pthread_mutex_unlock(&philo->lock_philo);		
			if (philo->index % 2 == 0)
				ft_start_eating(philo, philo->left_fork, philo->right_fork); //2nd arg is the 1st fork to block, 3rd arg is the 2nd fork to block
			else
				ft_start_eating(philo, philo->right_fork, philo->left_fork);	
			ft_start_sleeping(philo);
			ft_start_thinking(philo);	
		}
		usleep(1);
	}
	return (0);
}
