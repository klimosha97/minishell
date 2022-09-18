/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:52:02 by                   #+#    #+#             */
/*   Updated: 2021/10/16 15:52:02 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isprint(int a)
{
	if (a > 31 && a < 127)
		return (1);
	return (0);
}

int	ft_isnotspec(int a)
{
	if (a > 32 && a < 127 && a != 36 && a != 34 && a != 39 && a != 59
		&& a != 60 && a != 62 && a != 38 && a != '|')
		return (1);
	return (0);
}

int	ft_word(int a)
{
	if (a > 32 && a < 127 && a != 34 && a != 39 && a != 59 && a != 60
		&& a != 62 && a != 38 && a != '|')
		return (1);
	return (0);
}

int	ft_is_and(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '&')
		i++;
	if (i == 2)
		return (1);
	return (0);
}

int	ft_is_or(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '|')
		i++;
	if (i == 2)
		return (1);
	return (0);
}
