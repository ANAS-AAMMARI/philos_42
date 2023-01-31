/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:17:47 by aaammari          #+#    #+#             */
/*   Updated: 2023/01/31 12:32:05 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	chech_dead_philo(t_data *data)
{
	int				i;

	while (1)
	{
		i = -1;
		while (++i < data->nbr_of_philo)
		{
			usleep(1000);
			if (check_finish(data))
				return (1);
			if (get_time_ms() - data->philos[i].last_time_to_eat
				> (unsigned long)data->time_to_die)
			{
				data->finish = 1;
				pthread_mutex_lock(&data->print);
				printf("\033[0;31m%d died time: %lu\n",
					i + 1, get_time_ms() - data->create_at);
				return (1);
			}
		}
	}
	return (0);
}
// if (data->philos[i].num_of_eat == data->noe)
// 	return (1);

int	main(int ac, char **av)
{
	t_data		data;

	if (ac != 5 && ac != 6)
	{
		print_error("ERROR: wrong argc\n");
		return (0);
	}	
	data.finish = 0;
	if (!init_p(&data, ac, av))
	{
		print_error("ERROR: init\n");
		return (0);
	}
	create_philo(&data);
	return (0);
}
