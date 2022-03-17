/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:46:38 by vnafissi          #+#    #+#             */
/*   Updated: 2022/03/17 14:00:54 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void ft_start_eating(t_philo *philo)
{
	//int pthread_mutex_lock(pthread_mutex_t *mutex);
	printf("left fork %d locked=%d\n",philo->left_fork, pthread_mutex_lock(&philo->game->forks[philo->left_fork])); //in case lock fails, need to check
	printf("right fork %d locked=%d\n",philo->right_fork, pthread_mutex_lock(&philo->game->forks[philo->right_fork])); //in case lock fails, need to check

	gettimeofday(&philo->game->current_time, NULL);
	printf("%ld %d has taken a fork\n", philo->game->current_time.tv_sec * 1000, philo->index); //voir si il faut pas gérer autrement pour la précision des millisecondes

	philo->status = 0;

	gettimeofday(&philo->game->current_time, NULL);
	printf("%ld %d is eating\n", philo->game->current_time.tv_sec * 1000, philo->index);

	usleep(philo->game->time_to_eat * 1000);
	philo->nb_times_eat++;
	printf("%d ate %d times\n", philo->index, philo->nb_times_eat);

	philo->last_time_ate = philo->game->current_time.tv_sec * 1000;
	printf("left fork %d unlocked=%d\n",philo->left_fork, pthread_mutex_unlock(&philo->game->forks[philo->left_fork])); //in case unlock fails, need to check
	printf("right fork %d unlocked=%d\n",philo->right_fork, pthread_mutex_unlock(&philo->game->forks[philo->right_fork])); //in case unlock fails, need to check
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

void	*ft_dead_routine(void *arg)
{
	t_game	*game;
	//int		i;

	//The condition to go out of this while loop is if a philo is dead ==> put in place the other thread which tests indefinitely if a philo is dead
	game = (t_game*)arg;
	while (1)
	{
		printf("coucou2\n");
		//i = 0;
		printf("nb_philos=%d\n",game->nb_philos);
		printf("current_time=%ld\n",game->current_time.tv_sec);
		//while (i < game.nb_philos)
		//{
		//	printf("%d ate for the last time : %ld\n",game.philos[i].index, game.philos[i].last_time_ate);
		//	i++;
		//}
		usleep(1000 * 1000);
	}
	return (arg);
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
