

#include "./includes/philo.h"


int ft_start_eating(t_philo *philo, int first_fork, int second_fork)
{
	pthread_mutex_lock(&philo->game->forks[first_fork]); //in case lock fails, need to check
	printf("philo %d locked fork %d \n", philo->index, first_fork);
    printf("%ld %d has taken a fork\n", ft_gettime_since_game_start(philo->game->start_time), philo->index);
	
    pthread_mutex_lock(&philo->game->forks[second_fork]); //in case lock fails, need to check
	printf("philo %d locked fork %d \n", philo->index, second_fork);
	printf("%ld %d has taken a fork\n", ft_gettime_since_game_start(philo->game->start_time), philo->index);

	printf("%ld %d is eating\n", ft_gettime_since_game_start(philo->game->start_time), philo->index);
	ft_usleep(philo->game->time_to_eat);
	
    pthread_mutex_lock(&philo->lock_philo);
	printf("locked philo %d\n", philo->index);
    philo->nb_times_eat++;
	philo->last_meal = ft_gettimeofday_ms();
	pthread_mutex_unlock(&philo->lock_philo);
	printf("unlocked philo %d\n", philo->index);

    pthread_mutex_unlock(&philo->game->forks[second_fork]); //in case unlock fails, need to check
	printf("philo %d unlocked fork %d \n", philo->index, second_fork);
	pthread_mutex_unlock(&philo->game->forks[first_fork]); //in case unlock fails, need to check
	printf("philo %d unlocked fork %d \n", philo->index, first_fork);
	
    return (0);
}

int	ft_start_sleeping(t_philo *philo)
{
	//if (is_a_philo_dead(philo))
	//	return (1);
	printf("%ld %d is sleeping\n", ft_gettime_since_game_start(philo->game->start_time), philo->index);
	ft_usleep(philo->game->time_to_sleep);
	return (0);
}

int	ft_start_thinking(t_philo *philo)
{
	//if (is_a_philo_dead(philo))
	//	return (1);
	printf("%ld %d is thinking\n", ft_gettime_since_game_start(philo->game->start_time), philo->index);
	return (0);
}