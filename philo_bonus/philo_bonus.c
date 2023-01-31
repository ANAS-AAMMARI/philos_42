/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:00:40 by aaammari          #+#    #+#             */
/*   Updated: 2023/01/31 13:44:35 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// if the number of times each philosopher must eat is reached, stop simulation
// philosoher think
void	thinking(t_philo *philo)
{
	if (philo->num_of_eat != philo->data->noe)
		print_status(philo, "is thinking");
}

// philosoher eat
void	eating(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->data->print);
	printf("%lu Philosopher %d is eating\n", get_time_ms()
		-philo->data->create_at, philo->id_philo);
	philo->last_time_to_eat = get_time_ms();
	sem_post(philo->data->print);
	ft_usleep(philo->data->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

// philosoher sleep
void	sleeping(t_philo *philo)
{
	if (philo->num_of_eat != philo->data->noe)
	{
		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
	}
}

// philosoher routine
void	*routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = philo->id_philo;
	while (philo->data->noe != philo->num_of_eat)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		philo->num_of_eat++;
	}
	return (NULL);
}

// check if the philosoher is dead
void	*chech_dead_philo(t_philo *philo)
{
	while (1)
	{
		usleep(1000);
		if (check_finish(philo->data))
			return (NULL);
		if (get_time_ms() - philo->last_time_to_eat
			> (unsigned long)philo->data->time_to_die)
		{
			sem_wait(philo->data->print);
			printf("\033[0;31m%d died time: %lu\e[0;37m\n",
				philo->id_philo, get_time_ms() - philo->data->create_at);
			exit(1);
		}
	}
	return (NULL);
}
