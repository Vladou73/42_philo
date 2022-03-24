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
int	ft_dead_routine(t_game *game)
{
	int		i;
	
	ft_usleep(1);	
	while (1)
	{
		if (!ft_all_philos_have_eaten_enough(game))
			return (0);
		i = 0;
		while (i < game->nb_philos)
		{
			pthread_mutex_lock(&game->philos[i].lock_philo);
			if (ft_gettimeofday_ms() - game->philos[i].last_meal >= game->time_to_die && game->dead_philo == 0 && game->philos[i].nb_times_eat < game->nb_times_philos_must_eat)
			{
				pthread_mutex_unlock(&game->philos[i].lock_philo);
				pthread_mutex_lock(&game->lock_death);	
				game->dead_philo = 1;
				printf("%ld %d died\n", ft_gettime_since_game_start(game->start_time), game->philos[i].index);
				pthread_mutex_unlock(&game->lock_death);
				return (1);
			}
			pthread_mutex_unlock(&game->philos[i].lock_philo);
			i++;
		}
		ft_usleep(1);
	}
	return (0);
}

void	ft_printf(t_philo *philo, char* str)
{
	if (!is_a_philo_dead(philo) && !ft_all_philos_have_eaten_enough(philo->game))
		printf("%ld %d %s\n", ft_gettime_since_game_start(philo->game->start_time), philo->index, str);
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

int	ft_all_philos_have_eaten_enough(t_game *game)
{
	int i;
	int count_finished;

	if (game->nb_times_philos_must_eat < 0)
		return (0);
	i = 0;
	count_finished = 0;
	while (i < game->nb_philos)
	{
		pthread_mutex_lock(&game->philos[i].lock_philo);
		if (game->philos[i].nb_times_eat >= game->nb_times_philos_must_eat)
			count_finished++;
		pthread_mutex_unlock(&game->philos[i].lock_philo);
		i++;
	}
	if (count_finished == game->nb_philos)
		return (1);
	return (0);
}

int	ft_routine(t_philo *philo)
{
	//The condition to go out of this while loop is if a philo is dead ==> put in place the other thread which tests indefinitely if a philo is dead
	while (1)
	{
		if (is_a_philo_dead(philo))
			return (1);
		else
		{
			if (philo->index % 2 == 0)
				ft_start_eating(philo, philo->left_fork, philo->right_fork); //2nd arg is the 1st fork to block, 3rd arg is the 2nd fork to block
			else
				ft_start_eating(philo, philo->right_fork, philo->left_fork);	
			if (ft_all_philos_have_eaten_enough(philo->game) == 1)
				return (0);
			ft_start_sleeping(philo);
			ft_start_thinking(philo);
			ft_usleep(1);
		}
	}
	return (0);
}
