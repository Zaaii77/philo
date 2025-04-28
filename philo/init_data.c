/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 09:20:43 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/28 01:25:29 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_neg(t_data *data)
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

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (!pthread_mutex_init(&data->forks[i].fork, NULL))
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
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (NULL);
	data->forks = (t_fork *)malloc(sizeof(t_fork) * data->nb_philo);
	if (!data->forks)
		return (free(data->philo), NULL);
	if (init_forks(data) || init_philos(data))
		return (kill_forks(data), kill_philo(data), free(data), NULL);
	return (data);
}
