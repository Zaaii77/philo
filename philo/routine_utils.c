/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 01:28:43 by lowatell          #+#    #+#             */
/*   Updated: 2025/05/02 03:36:23 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stop_flag(t_data *data)
{
	pthread_mutex_lock(&data->stop);
	if (data->stop_f)
		return (pthread_mutex_unlock(&data->stop), 1);
	pthread_mutex_unlock(&data->stop);
	return (0);
}

int	philo_are_dead(t_data *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->dead);
		if (data->philo[i].is_dead)
			j++;
		pthread_mutex_unlock(&data->dead);
		pthread_mutex_lock(&data->meals);
		if (data->philo[i].meal_nb == data->meal_nb && data->meal_nb > -1)
			k++;
		pthread_mutex_unlock(&data->meals);
		i++;
	}
	if (j == data->nb_philo || k == data->nb_philo)
	{
		pthread_mutex_lock(&data->stop);
		data->stop_f = 1;
		return (pthread_mutex_unlock(&data->stop), 1);
	}
	return (0);
}

void	optiusleep(long time, long start, t_philo *philo)
{
	while (time > (gettime() - start))
	{
		usleep(5);
		if (stop_flag(philo->data))
			return ;
	}
}

int	lock_and_print(pthread_mutex_t *mutex, t_philo *philo)
{
	if (!pthread_mutex_lock(&philo->data->print))
			if (!pthread_mutex_lock(mutex))
				printf("%ld %ld has taken a fork\n",
				(gettime() - philo->data->start_time), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	return (1);
}