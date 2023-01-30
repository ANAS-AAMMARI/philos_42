/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:29:43 by aaammari          #+#    #+#             */
/*   Updated: 2023/01/30 18:44:18 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	init_sema(t_data *data)
{
	int	i;

	i = 0;
	sem_unlink("forks");
	sem_unlink("death");
	sem_unlink("print");
	data->forks = sem_open("forks", O_CREAT, 0700, data->nbr_of_philo);
	data->death = sem_open("death", O_CREAT, 0700, 1);
	data->print = sem_open("print", O_CREAT, 0700, 1);
	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philo);
	if (!data->philos || data->forks == SEM_FAILED
		|| data->death == SEM_FAILED || data->print == SEM_FAILED)
		exit(1);
	while (i < data->nbr_of_philo)
	{
		data->philos[i].id_philo = i + 1;
		data->philos[i].last_time_to_eat = get_time_ms();
		data->philos[i].num_of_eat = 0;
		data->philos[i].data = data;
		i++;
	}
}

int	init_data(t_data *data, int argc, char *argv[])
{
	parsing_arg(data, argc, argv);
	if (!check_data(data, argc))
		return (0);
	return (1);
}
