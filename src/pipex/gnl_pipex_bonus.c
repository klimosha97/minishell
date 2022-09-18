/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_pipex_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:10:17 by mcorneli          #+#    #+#             */
/*   Updated: 2022/02/02 15:10:27 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	strncmp_here_doc(const char *str1, const char *str2, size_t num)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	while (num-- > 0 && !(*s1 == '\0' && *s2 == '\0'))
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*str1 != '\n' && *(str1 + 1) != '\0')
		return (*s1 - '\n');
	return (0);
}

static char	*ft_strjoin1(char *line, char c)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
		i++;
	tmp = (char *)malloc(sizeof (char) * (i + 2));
	if (!tmp)
		exit(EXIT_FAILURE);
	while (j < i)
	{
		tmp[j] = line[j];
		j++;
	}
	tmp[j] = c;
	tmp[j + 1] = 0;
	free(line);
	return (tmp);
}

static int	get_next_line_pipex(char **line)
{
	char	*tmp;
	char	c;

	if (*line)
		free(*line);
	tmp = NULL;
	tmp = (char *)malloc(sizeof (char ));
	if (!tmp)
		exit(EXIT_FAILURE);
	tmp[0] = '\0';
	while (read(0, &c, 1) != 0 && c != '\n')
		tmp = ft_strjoin1(tmp, c);
	tmp = ft_strjoin1(tmp, '\n');
	*line = tmp;
	return (c == '\n');
}

void	ft_gnl_read(t_cmdinfo *cmd, int *pid)
{
	char	*str;

	str = NULL;
	while (get_next_line_pipex(&str))
	{
		if (strncmp_here_doc(str, cmd->delim, ft_strlen(cmd->delim)) == 0)
		{
			free(str);
			str = NULL;
			break ;
		}
		if (write(pid[1], str, ft_strlen(str)) == -1)
			exit(EXIT_FAILURE);
	}
	close(pid[1]);
	exit(0);
}
