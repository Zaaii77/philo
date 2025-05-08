/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:28:43 by lowatell          #+#    #+#             */
/*   Updated: 2025/05/08 18:28:45 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_think(t_philo *philo)
{
	if (check_stop_flag(philo->data))
		return (NULL);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %ld is thinking\n",
		(gettime() - philo->data->s_time), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	if (philo->id % 2 == 1)
		usleep(500);
	return (NULL);
}

int	check_stop_flag(t_data *data)
{
	pthread_mutex_lock(&data->stop);
	if (data->stop_f == 1)
		return (pthread_mutex_unlock(&data->stop), 1);
	pthread_mutex_unlock(&data->stop);
	return (0);
}

void	set_stop_flag(t_data *data, int i)
{
	pthread_mutex_lock(&data->stop);
	data->stop_f = i;
	pthread_mutex_unlock(&data->stop);
}

void	optiusleep(long time, long start, t_philo *philo)
{
	while (time > (gettime() - start))
	{
		usleep(200);
		if (check_stop_flag(philo->data))
			return ;
	}
}

int	lock_and_print(pthread_mutex_t *mutex, t_philo *philo)
{
	pthread_mutex_lock(mutex);
	if (check_stop_flag(philo->data))
	{
		pthread_mutex_unlock(mutex);
		return (0);
	}
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %ld has taken a fork\n",
		(gettime() - philo->data->s_time), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	return (1);
}
