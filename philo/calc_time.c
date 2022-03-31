/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:44:31 by vnafissi          #+#    #+#             */
/*   Updated: 2022/03/31 15:29:26 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

long int	ft_gettimeofday_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

long int	ft_gettime_since_game_start(long start_time)
{
	long	timeofday_ms;

	timeofday_ms = ft_gettimeofday_ms();
	return (timeofday_ms - start_time);
}

void	ft_usleep(long int time, t_philo *philo)
{
	long int	start;

	start = ft_gettimeofday_ms();
	while (ft_gettimeofday_ms() - start < time)
	{
		usleep(200);
		if (is_a_philo_dead(philo))
			break ;
	}
}
