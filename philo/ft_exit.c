/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:34:06 by vnafissi          #+#    #+#             */
/*   Updated: 2022/03/30 18:55:07 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	ft_free_null_ptr(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_exit(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->nb_philos)
	{
		pthread_mutex_destroy(&game->philos[i].lock_philo);
		pthread_mutex_destroy(&game->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&game->lock_death);
	ft_free_null_ptr((void **)&game->philos);
	ft_free_null_ptr((void **)&game->forks);
}
