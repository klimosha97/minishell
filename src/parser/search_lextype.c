/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_lextype.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:08:34 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 14:08:34 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	helper_1(char *str, int i, t_list *lex_list)
{
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
		{
			if (str[i + 2] == '<')
			{
				if (str[i + 3] == '<')
				{
					error_syntax(REDIR_IN);
					return (-1);
				}
				lex_list->type = REDIR_DISAPPEND;
				lex_list->last = i + 3;
				return (i + 3);
			}
			lex_list->type = HEREDOC;
			lex_list->last = i + 2;
			return (i + 2);
		}
		lex_list->type = REDIR_IN;
		lex_list->last = i + 1;
		return (i + 1);
	}
	else
		return (get_lex_type_helper_2(str, i, lex_list));
}

int	get_lex_type_helper_1(char *str, int i, t_list *lex_list)
{
	if (str[i] == '\'')
	{
		lex_list->type = QUOTES;
		i++;
		while (str[i] != '\0' && str[i] != '\'')
			i++;
		if (str[i] == '\0')
		{
			error_syntax(QUOTES);
			return (-1);
		}
		lex_list->last = i + 1;
		return (i + 1);
	}
	else
		return (helper_1(str, i, lex_list));
}

static int	helper(char *str, int i, t_list *lex_list)
{
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
		{
			if (str[i + 2] == '>')
			{
				error_syntax(REDIR_OUT);
				return (-1);
			}
			lex_list->type = REDIR_APPEND;
			lex_list->last = i + 2;
			return (i + 2);
		}
		lex_list->type = REDIR_OUT;
		lex_list->last = i + 1;
		return (i + 1);
	}
	else
		return (get_lex_type_helper_1(str, i, lex_list));
}

int	get_lex_type(char *str, int i, t_list *lex_list)
{
	lex_list->start = i;
	if (str[i] == ' ')
	{
		lex_list->type = SPACES;
		while (str[i] == ' ')
			i++;
		lex_list->last = i;
		return (i);
	}
	else if (ft_word(str[i]))
	{
		lex_list->type = WORD;
		while (ft_word(str[i]))
			i++;
		lex_list->last = i;
		return (i);
	}
	else
		return (helper(str, i, lex_list));
}
