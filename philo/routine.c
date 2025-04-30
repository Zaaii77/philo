/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 09:13:56 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/30 19:57:20 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_sleep(t_philo *philo)
{
	if (philo->is_dead || philo->is_eating)
		return (NULL);
	printf("%ld %ld is spleeping\n", (gettime() - philo->data->start_time), philo->id);
	usleep(philo->data->time_to_sleep);
	usleep(500);
	return (NULL);
}

void	*p_eat(t_philo *philo)
{
	if (philo->is_dead || (philo->meal_nb == philo->data->meal_nb && philo->data->meal_nb != 0))
		return (NULL);
	if (!pthread_mutex_lock(&philo->l_fork->fork))
{	printf("%ld %ld has taken a fork\n", (gettime() - philo->data->start_time), philo->id);
	if (!pthread_mutex_lock(&philo->r_fork->fork))
{	printf("%ld %ld has taken a fork\n", (gettime() - philo->data->start_time), philo->id);
	philo->is_eating = 1;
	printf("%ld %ld is eating\n", (gettime() - philo->data->start_time), philo->id);
	usleep(philo->data->time_to_eat);
	philo->meal_nb += 1;
	pthread_mutex_unlock(&philo->l_fork->fork);
	pthread_mutex_unlock(&philo->r_fork->fork);
	philo->is_eating = 0;
	philo->lst_meal = gettime();}}
	return (NULL);
}

void	is_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (!data->philo[i].is_dead && (gettime() - data->philo[i].lst_meal >= data->time_to_die) && !data->philo[i].is_eating)
		{
			printf("%ld %ld died\n", (gettime() - data->start_time), data->philo[i].id);
			data->philo[i].is_dead = 1;
		}
		i++;
	}
}

void	*routine(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_create(&data->philo[i].thread, NULL, (void *(*)(void *))p_eat, &data->philo[i]);
			pthread_create(&data->philo[i].thread, NULL, (void *(*)(void *))p_sleep, &data->philo[i]);
			pthread_join(data->philo[i].thread, NULL);
			is_dead(data);
			i++;
		}
	}
	return (NULL);
}