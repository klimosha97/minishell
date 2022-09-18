/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:08:23 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 15:24:01 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_group_status(t_list *lex_list)
{
	while (lex_list)
	{
		if (lex_list->type > 0 && lex_list->type != SPACES)
			return (GROUP_OK);
		lex_list = lex_list->next;
	}
	return (0);
}

static int	helper(t_list *lex_list, t_list *new)
{
	clear_t_list(lex_list);
	free(new);
	return (-1);
}

int	get_lexer_list(char *str, t_list **g_list, int i)
{
	t_list	*lex_list;
	t_list	*new;

	lex_list = NULL;
	while (str[i])
	{
		new = ft_lstnew(0);
		i = get_lex_type(str, i, new);
		if (i == -1)
			return (helper(lex_list, new));
		if (new->type == OR || new->type == AND)
		{
			free(new);
			(*g_list)->value = (void *) lex_list;
			(*g_list)->type = check_group_status(lex_list);
			return (i - 2);
		}
		ft_lstadd_back(&lex_list, new);
	}
	(*g_list)->value = (void *) lex_list;
	(*g_list)->type = check_group_status(lex_list);
	return (i);
}

static int	and_or(int i, char *str, t_list *new)
{
	if (ft_is_or(&str[i]))
	{
		new->type = OR;
		i += 2;
	}
	else if (ft_is_and(&str[i]))
	{
		new->type = AND;
		i += 2;
	}
	return (i);
}

t_list	*get_lexer(char *str)
{
	t_list	*group;
	t_list	*new;
	int		i;

	i = 0;
	group = NULL;
	while (str[i] != '\0')
	{
		new = ft_lstnew(0);
		if (ft_is_or(&str[i]) || ft_is_and(&str[i]))
			i = and_or(i, str, new);
		else
			i = get_lexer_list(str, &new, i);
		ft_lstadd_back(&group, new);
		new = NULL;
		if (i == -1)
		{
			g_sig.status = 2;
			clear_group_list(group);
			return (NULL);
		}
	}
	return (group);
}
