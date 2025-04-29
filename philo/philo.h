/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:48:05 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/29 19:11:22 by lowatell         ###   ########.fr       */
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
	pthread_t		id;
	long			lst_meal;
	int				is_dead;
	int				meal_nb;
	t_fork			*l_fork;
	t_fork			*r_fork;
	struct	s_data	*data;
	pthread_t		thread;
}	t_philo;

typedef	struct	s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_nb;
	long			start_time;
	t_philo			*philo;
	t_fork			*forks;
}	t_data;

t_data				*init_data(char **av);
int					ft_atoi(const char *str);
int					is_int(int nbr, char *str);
int					is_neg(t_data *data);
long				gettime(void);
void				kill_forks(t_data *data, int len);
void				*routine(t_philo *philo);

#endif