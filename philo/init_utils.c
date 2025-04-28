/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:15:23 by lowatell          #+#    #+#             */
/*   Updated: 2025/04/26 15:02:06 by lowatell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int	ft_size(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nbr;

	nbr = (long)n;
	i = ft_size(nbr);
	str = (char *)malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	if (nbr < 0)
		nbr *= -1;
	str[i--] = '\0';
	while (nbr > 0)
	{
		str[i] = nbr % 10 + '0';
		i--;
		nbr /= 10;
	}
	if (i == 0 && str[1] == '\0')
		str[i] = '0';
	else if (i == 0 && str[1] != '\0')
		str[i] = '-';
	return (str);
}

int	ft_atoi(const char *str)
{
	unsigned long long	nbr;
	int					sign;
	int					i;

	i = 0;
	sign = 1;
	nbr = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nbr > 9223372036854775807 && sign > 0)
			return (-1);
		if (nbr > 9223372036854775807 && sign < 0)
			return (0);
		nbr = (nbr * 10) + str[i] - '0';
		i++;
	}
	return (nbr * sign);
}

int	is_int(int nbr, char *str)
{
	char	*s;
	int		ret;

	s = ft_itoa(nbr);
	if (!s)
		return (1);
	ret = ft_strcmp(s, str);
	free(s);
	if (ret != 0)
		printf("Arguments must be < MAX_INT\n");
	return (ret);
}