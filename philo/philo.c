/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:52:13 by aaammari          #+#    #+#             */
/*   Updated: 2023/01/27 16:45:22 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	if (philo->num_of_eat != philo->data->noe)
		print_status(philo, "is thinking");
}

void	sleep_time(t_philo *philo)
{
	if (philo->num_of_eat != philo->data->noe)
	{
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	print_status(philo, "has taken a left fork");
	pthread_mutex_lock(philo->right);
	print_status(philo, "has taken a right fork");
	pthread_mutex_lock(&philo->data->print);
	printf("%lu Philosopher %d is eating\n", get_time_ms()
		-philo->data->create_at, philo->id_philo);
	philo->last_time_to_eat = get_time_ms();
	pthread_mutex_unlock(&philo->data->print);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = philo->id_philo;
	while (philo->data->finish == 0
		&& philo->data->noe != philo->num_of_eat)
	{
		eat(philo);
		sleep_time(philo);
		think(philo);
		philo->num_of_eat++;
	}
	return (NULL);
}

void	create_philo(t_data *data)
{
	int	i;

	i = 0;
	data->create_at = get_time_ms();
	while (i < data->nbr_of_philo)
	{
		pthread_create(&data->philos[i].thread, NULL,
			&routine, &data->philos[i]);
		usleep(100);
		i += 2;
	}
	i = 1;
	while (i < data->nbr_of_philo)
	{
		pthread_create(&data->philos[i].thread, NULL,
			&routine, &data->philos[i]);
		usleep(100);
		i += 2;
	}
	if (chech_dead_philo(data))
		return ;
	i = -1;
	while (++i < data->nbr_of_philo)
		pthread_join(data->philos[i].thread, NULL);
}
