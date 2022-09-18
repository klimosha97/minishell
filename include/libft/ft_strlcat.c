/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 20:27:15 by mcorneli          #+#    #+#             */
/*   Updated: 2021/10/05 20:36:24 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstsize;

	if (size == 0)
		return (ft_strlen(src));
	dstsize = ft_strlen(dst);
	dst = dstsize + dst;
	if (dstsize < size)
		return (ft_strlcpy(dst, src, size - dstsize) + dstsize);
	return (size + ft_strlen(src));
}
