/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaammari <aaammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:21:37 by aaammari          #+#    #+#             */
/*   Updated: 2023/01/31 12:58:41 by aaammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

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
	sem_t			*forks;
	sem_t			*print;
	sem_t			*death;
	unsigned long	create_at;
}	t_data;

typedef struct s_philo
{
	pid_t			pid;
	int				id_philo;
	int				num_of_eat;
	pthread_t		thread;
	t_data			*data;
	unsigned long	last_time_to_eat;
}	t_philo;

void			close_and_unlink_sema(t_data *data);
void			create_processes(t_data *data);
void			kill_processes(t_data *data);
void			parsing_arg(t_data *data, int argc, char *argv[]);
int				ft_atoi(const char *str);
int				print_error(char *str);
unsigned long	get_time_ms(void);
void			ft_usleep(unsigned long time_to_wait);
void			print_status(t_philo *philo, char *str);
void			init_sema(t_data *data);
void			*routine(void *arg);
void			*chech_dead_philo(t_philo *philo);
int				init_data(t_data *data, int argc, char *argv[]);
int				check_finish(t_data *data);

#endif