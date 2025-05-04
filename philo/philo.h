/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:48:05 by lowatell          #+#    #+#             */
/*   Updated: 2025/05/05 00:41:36 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <time.h>
# include <sys/time.h>

# define ARGS "Wrong arguments:\n./philo <amount_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> [amount_of_meals]\n"

struct s_data;

typedef	struct s_fork
{
	pthread_mutex_t	fork;
}	t_fork;

typedef	struct	s_philo
{
	long			id;
	long			lst_meal;
	int				is_eating;
	int				meal_nb;
	t_fork			*l_fork;
	t_fork			*r_fork;
	struct	s_data	*data;
	pthread_t		thread;
}	t_philo;

typedef	struct	s_data
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meal_nb;
	long			start_time;
	int				stop_f;
	pthread_mutex_t	eating;
	int				eating_init;
	pthread_mutex_t	last;
	int				last_init;
	pthread_mutex_t	print;
	int				print_init;
	pthread_mutex_t	count;
	int				count_init;
	pthread_mutex_t	stop;
	int				stop_init;
	t_philo			*philo;
	t_fork			*forks;
	pthread_t		monitor;
}	t_data;

t_data				*init_data(char **av);
int					ft_atoi(const char *str);
int					is_int(int nbr, char *str);
int					is_neg(t_data *data);
int					is_dead(t_data *data, int i);
long				gettime(void);
void				kill_forks(t_data *data, int len);
void				*p_eat(t_philo *philo);
void				*p_sleep(t_philo *philo);
void				*p_think(t_philo *philo);
void				*routine(t_philo *data);
void				optiusleep(long time, long start, t_philo *philo);
int					lock_and_print(pthread_mutex_t *mutex, t_philo *philo);
void				*monitoring(t_data *data);
void				routining(t_data *data);
int					check_stop_flag(t_data *data);
void				set_stop_flag(t_data *data, int i);
int					check_philos(t_data *data);
void				data_mutex(t_data *data, int i);
void				cleanup(t_data *data);
void				*one_case(t_philo *philo);

#endif