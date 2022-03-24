

#include "./includes/philo.h"


int ft_start_eating(t_philo *philo, int first_fork, int second_fork)
{
	pthread_mutex_lock(&philo->game->forks[first_fork]); //in case lock fails, need to check
	ft_printf(philo, "has taken a fork");
	
    pthread_mutex_lock(&philo->game->forks[second_fork]); //in case lock fails, need to check
	ft_printf(philo, "has taken a fork");

	ft_printf(philo, "is eating");
	ft_usleep(philo->game->time_to_eat);
	
    pthread_mutex_lock(&philo->lock_philo);
	philo->nb_times_eat++;
	philo->last_meal = ft_gettimeofday_ms();
	pthread_mutex_unlock(&philo->lock_philo);
	
    pthread_mutex_unlock(&philo->game->forks[second_fork]); //in case unlock fails, need to check
	pthread_mutex_unlock(&philo->game->forks[first_fork]); //in case unlock fails, need to check
	
    return (0);
}

int	ft_start_sleeping(t_philo *philo)
{
	ft_printf(philo, "is sleeping");
	ft_usleep(philo->game->time_to_sleep);
	return (0);
}

int	ft_start_thinking(t_philo *philo)
{
	ft_printf(philo, "is thinking");
	return (0);
}