/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:52:22 by                   #+#    #+#             */
/*   Updated: 2021/10/17 04:26:26 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *memptr, int val, size_t num)
{
	unsigned char	*p;

	p = (unsigned char *)memptr;
	while (num-- > 0)
	{
		if (*p == (unsigned char)val)
			return (p);
		p++;
	}
	return (NULL);
}
