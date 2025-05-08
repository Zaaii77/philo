/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:35:21 by lowatell          #+#    #+#             */
/*   Updated: 2025/05/08 18:35:32 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_case(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork->fork);
	printf("%ld %ld has taken a fork\n",
		(gettime() - philo->data->s_time), philo->id);
	optiusleep(philo->data->time_to_die, gettime(), philo);
	pthread_mutex_unlock(&philo->l_fork->fork);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %ld died\n", (gettime() - philo->data->s_time), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	return (NULL);
}

void	cleanup(t_data *data)
{
	kill_forks(data, data->nb_philo);
	data_mutex(data, 1);
	free(data);
}
