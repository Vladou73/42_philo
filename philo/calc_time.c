/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnafissi <vnafissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 15:44:31 by vnafissi          #+#    #+#             */
/*   Updated: 2022/03/21 15:14:31 by vnafissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

long int ft_gettimeofday_ms(void)
{
	struct timeval	current_time;
	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

long int ft_gettime_since_game_start(long start_time)
{
	long timeofday_ms;
	
	timeofday_ms = ft_gettimeofday_ms();
	return (timeofday_ms - start_time);
}

long int ft_gettime_since_last_meal(long last_meal)
{
	long timeofday_ms;
	
	timeofday_ms = ft_gettimeofday_ms();
	return (timeofday_ms - last_meal);
}