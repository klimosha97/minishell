/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:52:23 by                   #+#    #+#             */
/*   Updated: 2021/10/16 15:52:23 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *memptr1, const void *memptr2, size_t num)
{
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)memptr1;
	p2 = (unsigned char *)memptr2;
	while (num-- > 0)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++;
		p2++;
	}
	return (0);
}
