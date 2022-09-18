/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:52:50 by                   #+#    #+#             */
/*   Updated: 2021/10/17 03:20:03 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*set_word(const char *s, char c)
{
	size_t	i;
	char	*str;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	str = (char *) malloc(i * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**free_array(char **arr, size_t index)
{
	while (index-- > 0)
		free(arr[index]);
	free(arr);
	arr = NULL;
	return (arr);
}

char	**create_str(char **arr, const char *s, char c)
{
	size_t	i;
	size_t	g;

	i = 0;
	g = 0;
	while (s != NULL && s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			arr[g] = set_word(&s[i], c);
			if (arr[g] == NULL)
			{
				free_array(arr, g);
				return (NULL);
			}
			g++;
		}
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	arr[g] = NULL;
	return (arr);
}

char	**ft_split(const char *s, char c)
{
	char	**array;
	size_t	size_array;
	int		start;

	size_array = 0;
	start = 1;
	if (s != NULL)
	{
		while (s[start] != '\0')
		{
			if (s[start] == c && s[start - 1] != c)
				size_array += 1;
			start++;
		}
		if (s[start - 1] != c)
			size_array += 1;
	}
	array = (char **)malloc(size_array * sizeof(char *) + 1);
	if (!(array))
		return (NULL);
	array = create_str(array, s, c);
	if (array == NULL)
		return (NULL);
	return (array);
}
