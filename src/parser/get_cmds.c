/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:08:13 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 14:08:13 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_check_pipe_simi(t_list *lst)
{
	t_list	*tmp;

	tmp = lst->prev;
	while (tmp)
	{
		if (tmp->type > 4 && tmp->type < 14)
			return (1);
		else if (tmp->type > 1 && tmp->type < 5)
			break ;
		tmp = tmp->prev;
	}
	if (!tmp)
		return (1);
	return (0);
}

void	get_args(t_list *start, t_cmdinfo *cmd)
{
	int	i;

	i = 0;
	cmd->prog_args = (char **) malloc(sizeof (char *) * (cmd->size_args + 1));
	cmd->prog_args[cmd->size_args] = NULL;
	while (i < cmd->size_args)
	{
		if (start->type > 4 && start->type < 10)
		{
			start = start->next;
			if (start->type == SPACES)
				start = start->next;
		}
		else if (start->type > 1 && start->type < 5)
		{
			cmd->prog_args[i] = malloc(sizeof(char )
					* ft_strlen(start->value) + 1);
			if (!cmd->prog_args[i])
				exit(EXIT_FAILURE);
			ft_strlcpy(cmd->prog_args[i], start->value,
				ft_strlen(start->value) + 1);
			i++;
		}
		start = start->next;
	}
}

static t_cmdinfo	*pipe_or_semi(t_cmdinfo *cmd, t_list *start, t_list **g)
{
	if (ft_check_pipe_simi(*g))
	{
		error_syntax(PIPE);
		ft_lstdelone_cmd(cmd);
		cmd = NULL;
		return (cmd);
	}
	cmd->type = PIPE;
	get_args(start, cmd);
	*g = (*g)->next;
	return (cmd);
}

t_cmdinfo	*get_cmds(t_list **g_list, t_cmdinfo *cmd, t_main *mi)
{
	t_list	*start;
	char	*t;

	if (!cmd)
		return (NULL);
	start = *g_list;
	while (*g_list)
	{
		if ((*g_list)->type == PIPE || (*g_list)->type == SIMICOLON)
			return (pipe_or_semi(cmd, start, &*g_list));
		else if ((*g_list)->type > 1 && (*g_list)->type < 5)
		{
			t = get_word_value(*g_list, mi);
			(*g_list)->value = t;
			cmd->size_args++;
			while ((*g_list)->next && ((*g_list)->next->type > 1
					&& (*g_list)->next->type < 5))
				*g_list = (*g_list)->next;
		}
		else if ((*g_list)->type > 4 && (*g_list)->type < 10)
			*g_list = get_redirect(*g_list, cmd, mi);
		*g_list = (*g_list)->next;
	}
	get_args(start, cmd);
	return (cmd);
}

void	execute_group_level(t_list *g_list, t_main *mi)
{
	t_cmdinfo	*cmds;
	t_cmdinfo	*new;
	t_list		*tmp;

	cmds = NULL;
	tmp = g_list;
	while (tmp)
	{
		new = get_cmds(&tmp, ft_lstnew_cmd(), mi);
		if (!new)
		{
			clear_t_list(g_list);
			clear_t_cmdlist(cmds);
			g_list = NULL;
			return ;
		}
		ft_lstadd_back_cmd(&cmds, new);
		cmds->size_pipes++;
	}
	clear_t_list(g_list);
	g_list = NULL;
	mi->curr->value = NULL;
	execute(cmds, mi);
	clear_t_cmdlist(cmds);
	cmds = NULL;
}
