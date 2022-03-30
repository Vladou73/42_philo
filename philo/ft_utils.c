/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:21:52 by vnafissi          #+#    #+#             */
/*   Updated: 2022/03/30 18:22:27 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	ft_printf(t_philo *philo, char *str)
{
	if (!is_a_philo_dead(philo)
		&& !ft_all_philos_have_eaten_enough(philo->game))
		printf("%ld %d %s\n", ft_gettime_since_game_start(
				philo->game->start_time), philo->index, str);
}

int	ft_all_philos_have_eaten_enough(t_game *game)
{
	int	i;
	int	count_finished;

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
