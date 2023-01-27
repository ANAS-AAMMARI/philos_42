/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 09:49:01 by aaammari          #+#    #+#             */
/*   Updated: 2023/01/27 16:07:49 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	print_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(2, &str[i], 1);
	return (0);
}

void	print_status(t_philo *philo, char *str)
{
	unsigned long		ms;

	pthread_mutex_lock(&philo->data->print);
	ms = get_time_ms() - philo->data->create_at;
	printf("%lu Philosopher %d %s\n", ms, philo->id_philo, str);
	pthread_mutex_unlock(&philo->data->print);
}

void	destry_and_free_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philo)
	{
		pthread_mutex_destroy(data->philos[i].left);
		pthread_mutex_destroy(data->philos[i].right);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->philos);
	free(data->forks);
}
