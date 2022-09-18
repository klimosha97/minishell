/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:11:39 by mcorneli          #+#    #+#             */
/*   Updated: 2022/02/02 15:11:44 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	close_helper(int **pipes, t_cmdinfo *cmd, int pid[2])
{
	close_pipes(pipes, cmd->size_pipes - 1);
	ft_close_files(cmd);
	close(pid[0]);
	close(pid[1]);
}

static void	dupnclose_here_doc(int **pipes, int i, t_cmdinfo *cmd, int pid[2])
{
	if (cmd->size_pipes - 1 == 0)
	{
	}
	else if (i == 0)
		dup2(pipes[i][1], STDOUT_FILENO);
	else if (i == cmd->size_pipes - 1)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	if (cmd->fd_in != -1)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	else
		dup2(pid[0], STDIN_FILENO);
	if (cmd->fd_out != -1)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	close_helper(pipes, cmd, pid);
}

void	if_here_doc(t_cmdinfo *cmds, t_main *mi, int **pipes, int i)
{
	int	fid;
	int	pid[2];
	int	status;

	if (cmds->delim == NULL)
		return ;
	if (pipe(pid) == -1)
		exit(EXIT_FAILURE);
	fid = fork();
	if (fid < 0)
		exit(EXIT_FAILURE);
	if (fid == 0)
	{
		close_pipes(pipes, cmds->size_pipes - 1);
		ft_close_files(cmds);
		close(pid[0]);
		ft_gnl_read(cmds, pid);
	}
	waitpid(fid, &status, 0);
	dupnclose_here_doc(pipes, i, cmds, pid);
	clear_path_array_int(pipes, cmds->size_pipes - 1);
	exec_cmd(cmds, mi);
	exit(0);
}
