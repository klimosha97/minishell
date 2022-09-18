/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:07:20 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 14:07:30 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	build_echo(t_cmdinfo *cmd)
{
	int	flag;
	int	i;

	i = 1;
	flag = 0;
	if (cmd->prog_args[i])
	{
		while (cmd->prog_args[i] && !ft_strncmp(cmd->prog_args[i], "-n",
				ft_strlen(cmd->prog_args[i])))
		{
			++i;
			++flag;
		}
	}
	while (cmd->prog_args[i])
	{
		write(1, cmd->prog_args[i], ft_strlen(cmd->prog_args[i]));
		if (cmd->prog_args[i] + 1)
			write(1, " ", 1);
		++i;
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}

int	build_pwd(void)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	printf("%s\n", buf);
	free(buf);
	g_sig.status = 0;
	return (1);
}
