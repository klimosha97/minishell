/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_builds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:07:46 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 14:07:47 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_env(t_list *env)
{
	t_list	*start;

	start = env;
	while (start)
	{
		if (start->value)
			printf("%s=\"%s\"\n", start->key, (char *)start->value);
		start = start->next;
	}
}

static int	build_env(t_cmdinfo *cmd, t_main *mi)
{
	if (cmd->size_args != 1)
	{
		ft_error("env", NULL, "invalid option");
		g_sig.status = 1;
	}
	else
	{
		print_env(mi->my_env->en_list);
		g_sig.status = 0;
	}
	return (0);
}

int	check_build_in(t_cmdinfo *cmd, t_main *mi)
{
	if (ft_strncmpp(cmd->prog_args[0], "echo",
			ft_strlen(cmd->prog_args[0]) + 1) == 0)
		return (build_echo(cmd));
	else if (ft_strncmp(cmd->prog_args[0], "env",
			ft_strlen(cmd->prog_args[0]) + 1) == 0)
		return (build_env(cmd, mi));
	else if (ft_strncmp(cmd->prog_args[0], "export",
			ft_strlen(cmd->prog_args[0]) + 1) == 0)
		return (build_export(cmd, mi));
	else if (ft_strncmp(cmd->prog_args[0], "unset",
			ft_strlen(cmd->prog_args[0]) + 1) == 0)
		return (build_unset(cmd, mi));
	else if (ft_strncmp(cmd->prog_args[0], "pwd",
			ft_strlen(cmd->prog_args[0]) + 1) == 0)
		return (build_pwd());
	else if (ft_strncmp(cmd->prog_args[0], "cd",
			ft_strlen(cmd->prog_args[0]) + 1) == 0)
		return (build_cd(cmd, mi->my_env));
	else if (ft_strncmp(cmd->prog_args[0], "exit",
			ft_strlen(cmd->prog_args[0]) + 1) == 0)
		ft_exit(cmd->prog_args, mi, cmd);
	return (-3);
}
