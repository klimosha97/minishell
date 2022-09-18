/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:52:51 by                   #+#    #+#             */
/*   Updated: 2021/10/17 04:26:26 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *string, int symbol)
{
	char	*p;
	size_t	size;

	p = (char *)string;
	size = ft_strlen(p) + 2;
	while (size-- >= 2)
	{
		if (*p == (char)symbol)
			return (p);
		p++;
	}
	return (NULL);
}
