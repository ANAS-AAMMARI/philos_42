/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 10:34:17 by aaammari          #+#    #+#             */
/*   Updated: 2023/01/31 09:51:28 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philosopher(t_philo *philo)
{
	pthread_create(&philo->thread, NULL, (void *)chech_dead_philo, philo);
	routine(philo);
	pthread_join(philo->thread, NULL);
}

// create new process for each philosopher
void	create_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
		{
			philosopher(&data->philos[i]);
			exit(0);
		}
		i++;
	}
}

// kil all processes
void	kill_processes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_of_philo)
		kill(data->philos[i].pid, SIGKILL);
}
