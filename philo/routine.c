/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:13:56 by lowatell          #+#    #+#             */
/*   Updated: 2025/05/09 09:08:23 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_sleep(t_philo *philo)
{
	if (check_stop_flag(philo->data))
		return (NULL);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %ld is sleeping\n",
		(gettime() - philo->data->s_time), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	if (check_stop_flag(philo->data))
		return (NULL);
	optiusleep(philo->data->time_to_sleep, gettime(), philo);
	return (NULL);
}

void	*p_eat(t_philo *philo)
{
	if (check_stop_flag(philo->data))
		return (NULL);
	if (!lock_and_print(&philo->l_fork->fork, philo))
		return (NULL);
	if (!lock_and_print(&philo->r_fork->fork, philo))
		return (pthread_mutex_unlock(&philo->l_fork->fork), NULL);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %ld is eating\n", (gettime() - philo->data->s_time), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(&philo->data->last);
	philo->lst_meal = gettime();
	pthread_mutex_unlock(&philo->data->last);
	optiusleep(philo->data->time_to_eat, gettime(), philo);
	pthread_mutex_lock(&philo->data->count);
	philo->meal_nb += 1;
	pthread_mutex_unlock(&philo->data->count);
	pthread_mutex_unlock(&philo->l_fork->fork);
	pthread_mutex_unlock(&philo->r_fork->fork);
	return (NULL);
}

void	*routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 100);
	while (!check_stop_flag(philo->data))
	{
		p_eat(philo);
		p_sleep(philo);
		p_think(philo);
	}
	return (NULL);
}

void	routining(t_data *data)
{
	int	i;

	i = 0;
	if (data->nb_philo == 1)
	{
		pthread_create(&data->philo[i].thread, NULL,
			(void *(*)(void *))one_case, &data->philo[i]);
		pthread_join(data->philo[i].thread, NULL);
		return ;
	}
	while (i < data->nb_philo)
	{
		pthread_create(&data->philo[i].thread, NULL,
			(void *(*)(void *))routine, &data->philo[i]);
		i++;
	}
	i = 0;
	pthread_create(&data->monitor, NULL, (void *(*)(void *))monitoring, data);
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
}

void	*monitoring(t_data *data)
{
	while (1)
	{
		if (check_philos(data))
		{
			set_stop_flag(data, 1);
			break ;
		}
		usleep(500);
	}
	return (NULL);
}
