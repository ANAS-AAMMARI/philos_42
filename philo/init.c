/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:29:43 by aaammari          #+#    #+#             */
/*   Updated: 2023/01/28 15:15:45 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_data(t_data *data, int argc)
{
	if (argc == 6 && data->noe <= 0)
		return (print_error("ERROR: wrong number of times each\
 philosopher must eat\n"));
	if (data->nbr_of_philo < 1)
		return (print_error("ERROR: wrong number of philo\n"));
	if (data->time_to_die < 0)
		return (print_error("ERROR: wrong time to die\n"));
	if (data->time_to_eat < 0)
		return (print_error("ERROR: wrong time to eat\n"));
	if (data->time_to_sleep < 0)
		return (print_error("ERROR: wrong time to sleep\n"));
	return (1);
}

void	parsing_arg(t_data *data, int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return ;
	data->nbr_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->noe = ft_atoi(argv[5]);
	else
		data->noe = -1;
}

void	init_philo_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->print, NULL);
	while (i < data->nbr_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			printf("ERROR: mutex init faild\n");
			destry_and_free_philos(data);
			break ;
		}
		data->philos[i].id_philo = i + 1;
		data->philos[i].data = data;
		data->philos[i].left = &data->forks[i];
		data->philos[i].right = &data->forks[(i + 1) % data->nbr_of_philo];
		data->philos[i].num_of_eat = 0;
		data->philos[i].last_time_to_eat = get_time_ms();
		i++;
	}
}

int	init_p(t_data *data, int argc, char *argv[])
{
	parsing_arg(data, argc, argv);
	if (!check_data(data, argc))
		return (0);
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->nbr_of_philo);
	if (data->philos == NULL)
		return (0);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->nbr_of_philo);
	if (data->forks == NULL)
	{
		free(data->philos);
		return (0);
	}
	init_philo_mutex(data);
	return (1);
}

// int	check_finish(t_data *data)
// {
// 	int	nbr_of_eat;
// 	int	i;

// 	i = 0;
// 	nbr_of_eat = 0;
// 	while (i < data->nbr_of_philo)
// 	{
// 		if (data->philos[i].num_of_eat == data->noe)
// 			nbr_of_eat++;
// 		i++;
// 	}
// 	return (nbr_of_eat == data->nbr_of_philo);
// }
