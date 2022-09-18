/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:29:16 by mcorneli          #+#    #+#             */
/*   Updated: 2022/01/04 18:45:08 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	count_int(const char *str)
{
	long long	i;

	i = 0;
	while (*str)
	{
		if (!(*str > 47 && *str < 58))
		{
			write(1, "Error\n", 6);
			exit(1);
		}
		i = (i * 10) + *str - 48;
		str++;
	}
	return (i);
}

long long	ft_atoi(const char *string)
{
	long long	res;

	if (ft_strlen(string) > 11)
	{
		write(1, "Error\n", 6);
		exit(1);
	}
	if (*string == 45)
		res = count_int(string + 1) * -1;
	else
		res = count_int(string);
	if (res > 2147483647 || res < -2147483648)
	{
		write(1, "Error\n", 6);
		exit(1);
	}
	return (res);
}
