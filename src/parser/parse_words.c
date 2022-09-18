/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:08:30 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 14:08:30 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*parse_word(t_main *mi, int size, char *t)
{
	int		i;
	char	*str;

	i = -1;
	str = NULL;
	while (++i < size)
	{
		if (t[i] == '\\')
		{
			i++;
			str = ft_charjoin(str, t[i]);
		}
		else if (t[i] == '$')
		{
			if (t[i + 1] && t[i + 1] == '?')
				return (ft_itoa(g_sig.status));
			str = ft_strjoin_clean_all(str, get_dollar(&t[++i], mi));
			while (ft_isnotspec(t[i]))
				i++;
			i--;
		}
		else
			str = ft_charjoin(str, t[i]);
	}
	return (str);
}

char	*parse_quotes(int size, char *t)
{
	int		i;
	char	*str;

	i = 1;
	str = NULL;
	if (size == 1)
		return (ft_strdup(""));
	while (i < size)
	{
		str = ft_charjoin(str, t[i]);
		i++;
	}
	return (str);
}

static int	helper(char *t, int i)
{
	if (t[i] != '?')
	{
		while (ft_isnotspec(t[i]))
			i++;
	}
	else
		i++;
	i--;
	return (i);
}

static char	*helper1(char *t, int i, char *str)
{
	str = ft_charjoin(str, '\\');
	str = ft_charjoin(str, t[++i]);
	return (str);
}

char	*parse_double_quotes(t_main *mi, int size, char *t)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	if (size == 1)
		return (ft_strdup(""));
	while (++i < size)
	{
		if (t[i] == '\\')
		{
			if (t[i + 1] == '\\' || t[i + 1] == '$' || t[i + 1] == '"')
				str = ft_charjoin(str, t[++i]);
			else
				str = helper1(t, i, str);
		}
		else if (t[i] == '$')
		{
			str = ft_strjoin_clean_all(str, get_dollar(&t[++i], mi));
			i = helper(t, i);
		}
		else
			str = ft_charjoin(str, t[i]);
	}
	return (str);
}
