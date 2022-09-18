/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:47:24 by mcorneli          #+#    #+#             */
/*   Updated: 2021/10/05 19:47:41 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	char			*d;
	char			*s;

	d = (char *)dest;
	s = (char *)src;
	if (d > s)
	{
		d = d + count - 1;
		s = s + count - 1;
		while (count-- != 0)
		{
			*d = *s;
			d--;
			s--;
		}
		return (dest);
	}
	return (ft_memcpy(d, s, count));
}
