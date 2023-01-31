/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:26:31 by aaammari          #+#    #+#             */
/*   Updated: 2023/01/31 19:57:04 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// create philosoher processes
void	create_philo(t_data *data)
{
	data->create_at = get_time_ms();
	create_processes(data);
	waitpid(-1, NULL, 0);
	kill_processes(data);
	close_and_unlink_sema(data);
	free(data->philos);
}

// main function
int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (print_error("Wrong number of arguments\n"));
	if (!init_data(&data, argc, argv))
		return (1);
	init_sema(&data);
	create_philo(&data);
	return (0);
}
