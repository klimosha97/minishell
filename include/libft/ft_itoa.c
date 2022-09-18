/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:52:04 by                   #+#    #+#             */
/*   Updated: 2021/10/16 15:52:04 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	size_of_str(int n)
{
	size_t	len;

	len = 1;
	if (n == 0)
		return (1);
	if (n < 0)
		len += 1;
	while (abs(n / 10) > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

int	ft_abs(int n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

char	*put_num(char *str, size_t len, int n)
{
	str[len] = '\0';
	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (n < 0)
		str[0] = '-';
	while (n != 0)
	{
		str[--len] = ft_abs(n % 10) + 48;
		n /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*str;

	len = size_of_str(n);
	str = (char *) malloc(len * sizeof(char) + 1);
	if (!(str))
		return (NULL);
	str = put_num(str, len, n);
	return (str);
}
