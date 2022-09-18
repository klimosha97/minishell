/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_lextype1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:08:39 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 14:08:40 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	helper_3(char *str, int i, t_list *lex_list)
{
	if (str[i] == '&')
	{
		if (str[i + 1] == '&')
		{
			if (str[i + 2] == '&')
			{
				error_syntax(UMPERS);
				return (-1);
			}
			lex_list->type = AND;
			return (i + 2);
		}
		lex_list->type = WORD;
		lex_list->last = i + 1;
		return (i + 1);
	}
	return (i);
}

int	get_lex_type_helper_3(char *str, int i, t_list *lex_list)
{
	if (str[i] == '|')
	{
		if (str[i + 1] == '|')
		{
			if (str[i + 2] == '|')
			{
				error_syntax(PIPE);
				return (-1);
			}
			lex_list->type = OR;
			return (i + 2);
		}
		lex_list->type = PIPE;
		lex_list->last = i + 1;
		return (i + 1);
	}
	else
		return (helper_3(str, i, lex_list));
}

static int	helper_2(char *str, int i, t_list *lex_list)
{
	if (str[i] == ';')
	{
		if (str[i + 1] == ';')
		{
			error_syntax(SIMICOLON);
			return (-1);
		}
		lex_list->type = SIMICOLON;
		lex_list->last = i + 1;
		return (i + 1);
	}
	else
		return (get_lex_type_helper_3(str, i, lex_list));
}

int	get_lex_type_helper_2(char *str, int i, t_list *lex_list)
{
	if (str[i] == '\"')
	{
		lex_list->type = DOUBLE_QUOTES;
		i++;
		while (str[i] != '\0' && str[i] != '\"')
			i++;
		if (str[i] == '\0')
		{
			error_syntax(DOUBLE_QUOTES);
			return (-1);
		}
		lex_list->last = i + 1;
		return (i + 1);
	}
	else
		return (helper_2(str, i, lex_list));
}
