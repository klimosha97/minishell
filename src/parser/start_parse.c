/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:08:44 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 14:08:44 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_group_list(t_list *group)
{
	if (group->type == OR || group->type == AND)
		return (error_syntax(group->type));
	while (group->next != NULL)
	{
		group = group->next;
		if (group->type != AND && group->type != OR)
			return (error_syntax(group->type));
		if (group->prev->type != GROUP_OK || group->next == NULL
			|| group->next->type != GROUP_OK)
			return (error_syntax(group->type));
		group = group->next;
	}
	return (0);
}

static void	stop_parse(t_main *mi, t_list **g_list)
{
	g_sig.status = 2;
	free(mi->str);
	mi->str = NULL;
	clear_group_list(*g_list);
}

void	start_parse(t_list **g_list, t_main *mi)
{
	if (mi->str[0] == '\0')
		return ;
	if (!(*g_list) || check_group_list(*g_list))
	{
		stop_parse(mi, g_list);
		return ;
	}
	while (*g_list)
	{
		if ((*g_list)->type == GROUP_OK)
			execute_group_level((*g_list)->value, mi);
		(*g_list)->value = NULL;
		*g_list = (*g_list)->next;
		mi->curr = *g_list;
		if ((*g_list) && (*g_list)->type == AND)
			if (g_sig.status != 0)
				break ;
		if ((*g_list) && (*g_list)->type == OR)
			if (g_sig.status == 0)
				break ;
	}
	free(mi->str);
	mi->str = NULL;
	clear_group_list(mi->head);
}
