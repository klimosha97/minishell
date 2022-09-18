/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:53:20 by                   #+#    #+#             */
/*   Updated: 2021/10/16 15:53:20 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	check(const char *set, char a)
{
	while (*set != '\0')
	{
		if (*set == a)
			return (1);
		set++;
	}
	return (0);
}

char	*to_up(char *s1, const char *set)
{
	while (check(set, *s1))
		s1++;
	return (s1);
}

char	*to_down(char *s1, const char *set)
{
	if (*s1 == '\0')
		return (s1);
	s1 = s1 + ft_strlen(s1) - 1;
	while (check(set, *s1))
		s1--;
	return (s1);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*p1;
	char	*p2;
	char	*res;

	if (!(s1 && set))
		return (NULL);
	p1 = (char *)s1;
	p1 = to_up(p1, set);
	p2 = to_down(p1, set);
	res = (char *)malloc((p2 - p1) * sizeof(char) + 2);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, p1, p2 - p1 + 2);
	return (res);
}
