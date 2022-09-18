/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:13:05 by mcorneli          #+#    #+#             */
/*   Updated: 2022/02/02 15:13:07 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_path_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

static char	*ft_strjoin_pipex(char *s1, const char *s2)
{
	char	*result;
	size_t	size1;
	size_t	size2;

	if (!(s1 && s2))
		return (NULL);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	result = (char *)malloc((size1 + size2) * sizeof(char) + 2);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, (size1 + size2) + 2);
	result[size1] = '/';
	result[size1 + 1] = '\0';
	size1 += 1;
	ft_strlcpy(&result[size1], s2, (size1 + size2) + 2);
	free(s1);
	return (result);
}

static char	*find_path_helper(char **path_arr, char *name)
{
	int		j;
	char	*path;

	j = 0;
	while (path_arr[j])
	{
		path_arr[j] = ft_strjoin_pipex(path_arr[j], name);
		if (access(path_arr[j], F_OK) == 0)
		{
			path = ft_strdup(path_arr[j]);
			clear_path_array(path_arr);
			return (path);
		}
		j++;
	}
	clear_path_array(path_arr);
	return (NULL);
}

char	*find_path(char **env, char *name)
{
	int		j;
	char	*path;
	char	**path_arr;

	j = 0;
	while (env[j] && ft_strncmp(env[j], "PATH", 4) != 0)
		j++;
	if (!env[j])
		return (NULL);
	path = ft_substr(env[j], 5, ft_strlen(&env[j][5]));
	path_arr = ft_split(path, ':');
	free(path);
	path = NULL;
	path = find_path_helper(path_arr, name);
	if (path)
		return (path);
	return (NULL);
}
