/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:08:50 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 14:15:27 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	absolute_path(t_cmdinfo *cmd, t_main *mi)
{
	if (access(cmd->prog_args[0], F_OK) == 0)
	{
		execve(cmd->prog_args[0], cmd->prog_args, mi->my_env->env);
		return ;
	}
	else
	{
		ft_error(cmd->prog_args[0], NULL, ": command not found");
		clear_t_cmdlist(cmd);
		clear_t_main(mi);
		exit(127);
	}
}

static void	exec_with_path(t_main *mi, t_cmdinfo *cmd)
{
	char	*path;

	path = NULL;
	path = find_path(mi->my_env->my_env, cmd->prog_args[0]);
	if (path == NULL)
	{
		ft_error(cmd->prog_args[0], NULL, ": command not found");
		clear_t_cmdlist(cmd);
		clear_t_main(mi);
		exit(127);
	}
	execve(path, cmd->prog_args, mi->my_env->env);
	free(path);
}

void	exec_cmd(t_cmdinfo *cmd, t_main *mi)
{
	t_list	*tmp;

	create_envp_arr(mi->my_env);
	tmp = NULL;
	tmp = find_env_elem("PATH", mi->my_env->en_list);
	if (cmd->prog_args[0][0] == '.' || cmd->prog_args[0][0] == '/')
		absolute_path(cmd, mi);
	else if (tmp == NULL)
	{
		ft_error(cmd->prog_args[0], NULL, ": command not found");
		clear_t_cmdlist(cmd);
		clear_t_main(mi);
		exit(127);
	}
	else
		exec_with_path(mi, cmd);
	clear_t_cmdlist(cmd);
	clear_t_main(mi);
	exit(EXIT_FAILURE);
}
