/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:20:43 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/29 02:55:53 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philos(t_data *data)
{
	data->philo = (t_philo *)malloc(sizeof(t_fork) * data->nb_philo);
	if (!data->philo)
		return (kill_forks(data, data->nb_philo), 1);
	return (0);
}

static int	init_forks(t_data *data)
{
	int	i;

	data->forks = (t_fork *)malloc(sizeof(t_fork) * data->nb_philo);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i].fork, NULL))
			return (kill_forks(data, i), 1);
		i++;
	}
	return (0);
}

t_data	*init_data(char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->meal_nb = 0;
	if (av[5])
		data->meal_nb = ft_atoi(av[5]);
	if (is_int(data->nb_philo, av[1]) || is_int(data->time_to_die, av[2])
		|| is_int(data->time_to_eat, av[3]) || is_int(data->time_to_sleep, av[4])
		|| (av[5] && is_int(data->meal_nb, av[5])) || is_neg(data))
		return (NULL);
	if (init_forks(data) || init_philos(data))
		return (free(data), NULL);
	data->start_time = gettime();
	return (data);
}
