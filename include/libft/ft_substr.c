/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:53:23 by                   #+#    #+#             */
/*   Updated: 2021/10/16 16:19:04 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*s1;
	char	*result;

	s1 = (char *)s;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	if (ft_strlen(&s1[start]) > len)
	{
		result = (char *)malloc(len * sizeof(char) + 1);
		if (result == NULL)
			return (NULL);
		ft_strlcpy(result, &s1[start], len * sizeof(char) + 1);
		return (result);
	}
	result = (char *) malloc(ft_strlen(&s1[start]) * sizeof(char) + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, &s1[start], ft_strlen(&s1[start]) * sizeof(char)
		+ 1);
	return (result);
}
