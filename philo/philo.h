/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:21:37 by aaammari          #+#    #+#             */
/*   Updated: 2023/01/28 15:16:01 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/* noe = nbr_of_times_must_eat */

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				noe;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	unsigned long	create_at;
	int				finish;
}	t_data;

typedef struct s_philo
{
	int				id_philo;
	int				num_of_eat;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_t		thread;
	t_data			*data;
	unsigned long	last_time_to_eat;
}	t_philo;

int				init_p(t_data *data, int argc, char *argv[]);
void			parsing_arg(t_data *data, int argc, char *argv[]);
int				ft_atoi(const char *str);
int				print_error(char *str);
void			eat(t_philo *philo);
void			think(t_philo *philo);
void			sleep_time(t_philo *philo);
void			create_philo(t_data *data);
void			print_status(t_philo *philo, char *str);
unsigned long	get_time_ms(void);
void			ft_usleep(unsigned long time_to_wait);
void			destry_and_free_philos(t_data *data);
int				chech_dead_philo(t_data *data);

#endif