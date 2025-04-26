/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:45:38 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/26 13:15:05 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	(void)ac;
	data = init_data(av);
	if (!data)
		return (1);
	printf("%d\n", data->nb_philo);
	return (0);
}
