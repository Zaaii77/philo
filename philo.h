/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:48:05 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/22 14:52:04 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>

typedef	struct s_fork
{
	void			*fork;
	struct	s_fork	*next;	
}	t_fork;

typedef	struct	s_philo
{
	int	id;
	int	time_sleep;
	int	time_eat;
}	t_philo;

#endif