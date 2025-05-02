/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:13:56 by lowatell          #+#    #+#             */
/*   Updated: 2025/05/02 03:46:12 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_sleep(t_philo *philo)
{
	if (philo->is_dead || philo->is_eating)
		return (NULL);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %ld is spleeping\n", (gettime() - philo->data->start_time), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	optiusleep(philo->data->time_to_sleep, gettime(), philo);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %ld is thinking\n", (gettime() - philo->data->start_time), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	return (NULL);
}

void	*p_eat(t_philo *philo)
{
	if (philo->is_dead || (philo->meal_nb == philo->data->meal_nb && philo->data->meal_nb != 0))
		return (NULL);
	if (lock_and_print(&philo->l_fork->fork, philo))
		lock_and_print(&philo->r_fork->fork, philo);
	philo->is_eating = 1;
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %ld is eating\n", (gettime() - philo->data->start_time), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	optiusleep(philo->data->time_to_eat, gettime(), philo);
	pthread_mutex_lock(&philo->data->meals);
	philo->meal_nb += 1;
	pthread_mutex_unlock(&philo->data->meals);
	pthread_mutex_unlock(&philo->l_fork->fork);
	pthread_mutex_unlock(&philo->r_fork->fork);
	philo->is_eating = 0;
	philo->lst_meal = gettime();
	return (NULL);
}

void	*routine(t_philo *philo)
{
	while (!stop_flag(philo->data))
	{
		p_eat(philo);
		p_sleep(philo);
	}
	return (NULL);
}

void	routining(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&data->philo[i].thread, NULL, (void *(*)(void *))routine, &data->philo[i]);
		i++;
	}
	i = 0;
	pthread_create(&data->monitor, NULL, (void *(*)(void *))monitoring, &data);
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
}

void	*monitoring(t_data *data)
{
	while (!philo_are_dead(data))
		is_dead(data);
	return (NULL);
}