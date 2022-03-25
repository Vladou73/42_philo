
#include "./includes/philo.h"

//reprendre ma fonction free null depuis mon push swap

void    ft_exit(t_game *game)
{
    int i;

    i = 0;
    while (i < game->nb_philos)
    {
        pthread_mutex_destroy(&game->philos[i].lock_philo);
        pthread_mutex_destroy(&game->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&game->lock_death);
    free(game->philos);
    free(game->forks);
}