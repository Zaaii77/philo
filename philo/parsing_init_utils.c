/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:51:42 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/29 02:56:39 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	struct	timeval tv;

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
