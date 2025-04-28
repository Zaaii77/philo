/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:48:05 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/28 01:24:16 by lowatell         ###   ########.fr       */
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

typedef	struct s_fork
{
	pthread_mutex_t	fork;
}	t_fork;

typedef	struct	s_philo
{
	pthread_t		id;
	t_fork			*l_fork;
	t_fork			*r_fork;
}	t_philo;

typedef	struct	s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_nb;
	t_philo			*philo;
	t_fork			*forks;
}	t_data;

t_data				*init_data(char **av);
int					ft_atoi(const char *str);
int					is_int(int nbr, char *str);

#endif