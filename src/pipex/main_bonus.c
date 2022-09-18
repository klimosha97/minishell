/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:12:31 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 15:27:33 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	dupnclose_pipes(int **pipes, int i, int size_pipe, t_cmdinfo *cmd)
{
	if (size_pipe == 0)
	{
	}
	else if (i == 0)
		dup2(pipes[i][1], STDOUT_FILENO);
	else if (i == size_pipe)
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
	if (cmd->fd_out != -1)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	close_pipes(pipes, size_pipe);
	ft_close_files(cmd);
}

static void	kernel_child(t_cmdinfo *cmds, int i, int *fid)
{
	ft_open_files(cmds);
	fid[i] = fork();
	if (fid[i] < 0)
		exit(EXIT_FAILURE);
	change_signal();
}

static void	close_helper(int **pipes, int size)
{
	close_pipes(pipes, size - 1);
	clear_path_array_int(pipes, size - 1);
}

void	start_exec(int size, t_cmdinfo *cmds, t_main *mi, int *fid)
{
	int	i;
	int	**pipes;

	i = -1;
	pipes = NULL;
	pipes = pipe_init(pipes, size - 1);
	while (cmds && ++i < size)
	{
		kernel_child(cmds, i, fid);
		if (fid[i] == 0)
		{
			free(fid);
			clear_group_list(mi->head);
			if_here_doc(cmds, mi, pipes, i);
			dupnclose_pipes(pipes, i, size - 1, cmds);
			clear_path_array_int(pipes, size - 1);
			if (check_build_in(cmds, mi) != -3)
				exit(g_sig.status);
			exec_cmd(cmds, mi);
			exit(0);
		}
		ft_close_files(cmds);
		cmds = cmds->next;
	}
	close_helper(pipes, size);
}

void	execute(t_cmdinfo *cmds, t_main *mi)
{
	int	status;
	int	*fid;
	int	i;

	if (cmds->size_pipes == 1)
	{
		status = check_build_in(cmds, mi);
		if (status != -3)
			return ;
	}
	fid = (int *) malloc(sizeof(int ) * cmds->size_pipes);
	if (!fid)
		exit(EXIT_FAILURE);
	start_exec(cmds->size_pipes, cmds, mi, fid);
	i = 0;
	while (i < cmds->size_pipes)
	{
		if (waitpid(fid[i], &mi->status, WUNTRACED) == -1)
			exit(EXIT_FAILURE);
		set_exit_code(mi->status);
		i++;
	}
	free(fid);
	fid = NULL;
}
