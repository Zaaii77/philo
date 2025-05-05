/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:51:42 by lowatell          #+#    #+#             */
/*   Updated: 2025/05/05 20:34:55 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_data *data, int i)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&data->eating);
	pthread_mutex_lock(&data->last);
	if (data->philo[i].is_eating == 0
		&& (gettime() - data->philo[i].lst_meal) >= data->time_to_die)
	{
		set_stop_flag(data, 1);
		pthread_mutex_lock(&data->print);
		printf("%ld %ld died\n", (gettime() - data->s_time), data->philo[i].id);
		pthread_mutex_unlock(&data->print);
		res = 1;
	}
	pthread_mutex_unlock(&data->eating);
	pthread_mutex_unlock(&data->last);
	return (res);
}

int	is_neg(t_data *data)
{
	if (data->meal_nb < 0)
		return (printf("meals number must be > 1\n"), 1);
	if (data->nb_philo < 1)
		return (printf("philo number must be > 0\n"), 1);
	if (data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0)
		return (printf("times must be positives\n"), 1);
	return (0);
}

long	gettime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	kill_forks(t_data *data, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		pthread_mutex_destroy(&data->forks[i].fork);
		i++;
	}
	free(data->forks);
	data->forks = NULL;
}

int	check_philos(t_data *data)
{
	int			i;
	static int	j;

	i = -1;
	j = 0;
	while (++i < data->nb_philo)
	{
		if (is_dead(data, i))
			return (1);
		pthread_mutex_lock(&data->count);
		if (data->philo[i].meal_nb == data->meal_nb)
			j++;
		pthread_mutex_unlock(&data->count);
	}
	if (j == data->nb_philo)
	{
		set_stop_flag(data, 1);
		pthread_mutex_lock(&data->print);
		printf("Nice ! Each philosophers eat %d time(s) !\n", data->meal_nb);
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	return (0);
}
