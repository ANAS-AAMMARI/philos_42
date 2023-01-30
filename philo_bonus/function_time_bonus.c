/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_time_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:09:07 by aaammari          #+#    #+#             */
/*   Updated: 2023/01/28 15:08:14 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned long	get_time_ms(void)
{
	struct timeval	now;
	unsigned long	time_ms;

	gettimeofday(&now, NULL);
	time_ms = now.tv_sec * 1000 + now.tv_usec / 1000;
	return (time_ms);
}

void	ft_usleep(unsigned long time_to_wait)
{
	unsigned long	time;

	time = get_time_ms();
	while (get_time_ms() < time + time_to_wait)
		usleep(500);
}
