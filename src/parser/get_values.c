/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:08:18 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 14:08:19 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_search_key(char *key, t_list *en_lst)
{
	while (en_lst)
	{
		if (ft_strncmp(key, en_lst->key, ft_strlen(key)) == 0)
		{
			free(key);
			return (ft_strdup(en_lst->value));
		}
		en_lst = en_lst->next;
	}
	free(key);
	return (ft_strdup(""));
}

char	*get_dollar(char *str, t_main *mi)
{
	int		i;
	char	*key;

	i = 0;
	if (!str)
		return (ft_strdup("$"));
	if (*str == '?')
		return (ft_itoa(g_sig.status));
	while (str[i] && ft_isnotspec(str[i]))
		i++;
	if (i == 0)
		return (ft_strdup(""));
	key = ft_substr(str, 0, i);
	return (ft_search_key(key, mi->my_env->en_list));
}

char	*get_word_value(t_list *lst, t_main *mi)
{
	char	*t;
	int		size;
	char	*word;

	word = NULL;
	t = NULL;
	while (lst && lst->type > 1 && lst->type < 5)
	{
		size = lst->last - lst->start;
		t = malloc(size + 1);
		if (!t)
			exit(EXIT_FAILURE);
		ft_strlcpy(t, &mi->str[lst->start], size + 1);
		if (lst->type == WORD)
			word = ft_strjoin_clean_all(word, parse_word(mi, size, t));
		else if (lst->type == QUOTES)
			word = ft_strjoin_clean_all(word, parse_quotes(size - 1, t));
		else if (lst->type == DOUBLE_QUOTES)
			word = ft_strjoin_clean_all(word,
					parse_double_quotes(mi, size - 1, t));
		lst = lst->next;
		free(t);
		t = NULL;
	}
	return (word);
}

static t_list	*helper1(t_list *lst, t_cmdinfo *cmd, t_main *mi)
{
	if (lst->type == REDIR_IN)
	{
		while (lst->next->type == SPACES)
			lst = lst->next;
		cmd->file_in = get_word_value(lst->next, mi);
		if (!cmd->file_in)
			error_syntax(0);
	}
	else if (lst->type == REDIR_APPEND)
	{
		while (lst->next->type == SPACES)
			lst = lst->next;
		cmd->file_out = get_word_value(lst->next, mi);
		cmd->chmod = 2;
		if (!cmd->file_out)
			error_syntax(0);
	}
	return (lst->next);
}

t_list	*get_redirect(t_list *lst, t_cmdinfo *cmd, t_main *mi)
{
	if (lst->type == HEREDOC)
	{
		while (lst->next->type == SPACES)
			lst = lst->next;
		cmd->delim = get_word_value(lst->next, mi);
		if (!cmd->delim)
			error_syntax(0);
	}
	else if (lst->type == REDIR_OUT)
	{
		while (lst->next->type == SPACES)
			lst = lst->next;
		cmd->file_out = get_word_value(lst->next, mi);
		cmd->chmod = 1;
		if (!cmd->file_out)
			error_syntax(0);
	}
	else
		return (helper1(lst, cmd, mi));
	return (lst->next);
}
