/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:52:53 by                   #+#    #+#             */
/*   Updated: 2021/10/16 15:52:53 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	sizesrc;
	size_t	sizedest;
	char	*dublicate;

	sizesrc = ft_strlen(str);
	dublicate = malloc(sizesrc * sizeof(char) + 1);
	if (dublicate == NULL)
		return (NULL);
	sizedest = ft_strlcpy(dublicate, str, sizesrc + 1);
	if (sizedest == sizesrc)
		return (dublicate);
	return (NULL);
}
