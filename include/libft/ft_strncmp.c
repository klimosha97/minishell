/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:53:15 by                   #+#    #+#             */
/*   Updated: 2021/10/17 03:12:37 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

#include <stdio.h>
#include <string.h>

int	ft_strncmp(const char *string1, const char *string2, size_t num)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)string1;
	s2 = (unsigned char *)string2;
	while (num-- > 0 && !(*s1 == '\0' && *s2 == '\0'))
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

int	ft_strncmpp(const char *string1, const char *string2, size_t num)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)string1;
	s2 = (unsigned char *)string2;
	num = 1;
	while (--num > 0 && !(*s1 == '\0' && *s2 == '\0'))
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (1);
}
