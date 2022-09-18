/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:13:25 by mcorneli          #+#    #+#             */
/*   Updated: 2022/02/02 15:13:26 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	**pipe_init(int **pipes, int size)
{
	int	i;

	if (size == 0)
		return (NULL);
	pipes = (int **) malloc(sizeof(int *) * size);
	if (!pipes)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < size)
	{
		pipes[i] = (int *)malloc(sizeof(int ) * 2);
		if (!pipes[i])
		{
			clear_path_array_int(pipes, size);
			ft_error("error open pipe", NULL, strerror(errno));
		}
		if (pipe(pipes[i]) == -1)
		{
			clear_path_array_int(pipes, size);
			ft_error("error open pipe", NULL, strerror(errno));
		}
		i++;
	}
	return (pipes);
}

int	ft_open_files(t_cmdinfo *cmd)
{
	if (cmd->file_out)
	{
		if (cmd->chmod == 1)
			cmd->fd_out = open(cmd->file_out, O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
		else if (cmd->chmod == 2)
			cmd->fd_out = open(cmd->file_out, O_WRONLY | O_APPEND
					| O_CREAT, 0644);
		if (cmd->fd_out == -1)
			ft_error(cmd->prog_args[0], NULL, strerror(errno));
	}
	if (cmd->file_in)
	{
		cmd->fd_in = open(cmd->file_in, O_RDONLY);
		if (cmd->fd_in == -1)
			ft_error(cmd->prog_args[0], NULL, strerror(errno));
	}
	return (0);
}

void	ft_close_files(t_cmdinfo *cmds)
{
	if (cmds->fd_in != -1)
		close(cmds->fd_in);
	if (cmds->fd_out != -1)
		close(cmds->fd_out);
}

void	close_pipes(int **pipes, int size)
{
	int	j;

	j = 0;
	while (j < size)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}
