/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 09:49:01 by aaammari          #+#    #+#             */
/*   Updated: 2023/01/31 13:49:30 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// convert string to integer
int	ft_atoi(const char *str)
{
	int	i;
	int	k;
	int	s;

	i = 0;
	k = 0;
	s = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		k = (k * 10) + (str[i] - 48);
		i++;
	}
	return (k * s);
}

// print error message
int	print_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(2, &str[i], 1);
	return (0);
}

// print status of philosopher
void	print_status(t_philo *philo, char *str)
{
	unsigned long		ms;

	sem_wait(philo->data->print);
	ms = get_time_ms() - philo->data->create_at;
	printf("%lu Philosopher %d %s\n", ms, philo->id_philo, str);
	sem_post(philo->data->print);
}

// close and unlink semaphores
void	close_and_unlink_sema(t_data *data)
{
	if (data->forks)
	{
		sem_close(data->forks);
		sem_unlink("forks");
	}
	if (data->death)
	{
		sem_close(data->death);
		sem_unlink("death");
	}
	if (data->print)
	{
		sem_close(data->print);
		sem_unlink("print");
	}
}

// check if all philosophers ate enough
int	check_finish(t_data *data)
{
	int	nbr_of_eat;
	int	i;

	i = 0;
	nbr_of_eat = 0;
	while (i < data->nbr_of_philo)
	{
		if (data->philos[i].num_of_eat == data->noe)
			nbr_of_eat++;
		i++;
	}
	return (nbr_of_eat == data->nbr_of_philo);
}
