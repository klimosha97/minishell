/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:53:16 by                   #+#    #+#             */
/*   Updated: 2021/10/17 04:26:26 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *string1, const char *string2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*string2)
		return ((char *)string1);
	while (string1[i] != '\0' && i < len)
	{
		if (string1[i] == string2[0])
		{
			j = 0;
			while (string2[j] != '\0' && string1[i + j] == string2[j] && i
				+ j < len)
			{
				if (string2[j + 1] == '\0')
					return ((char *)&string1[i]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
