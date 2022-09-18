/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:07:14 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 14:07:29 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_option(const char *str)
{
	int	exit_code;

	exit_code = 0;
	if (*str == '-')
		exit_code = 1;
	return (exit_code);
}

static int	change_pwd(t_list *pwd)
{
	char	*tmp;

	if (!pwd)
		return (EXIT_FAILURE);
	tmp = pwd->value;
	pwd->value = getcwd(NULL, 0);
	if (!pwd->value)
		return (1);
	if (tmp)
		free(tmp);
	return (0);
}

static int	cd_home(t_env *env)
{
	t_list	*tmp;
	char	*home;
	int		exit_code;

	exit_code = change_pwd(find_env_elem("OLDPWD", env->en_list));
	tmp = find_env_elem("HOME", env->en_list);
	if (!tmp)
		return (ft_error("cd", NULL, strerror(errno)));
	home = tmp->value;
	exit_code = chdir(home);
	if (exit_code < 0)
		return (ft_error("cd", NULL, strerror(errno)));
	change_pwd(find_env_elem("PWD", env->en_list));
	return (0);
}

int	build_cd(t_cmdinfo *cmd, t_env *env)
{
	int	exit_code;

	exit_code = change_pwd(find_env_elem("OLDPWD", env->en_list));
	if (!*(cmd->prog_args + 1))
		return (cd_home(env));
	if (check_option(*(cmd->prog_args + 1)) == EXIT_FAILURE)
		return (error_usage("cd", *(cmd->prog_args + 1)));
	exit_code = chdir(*(cmd->prog_args + 1));
	if (exit_code < 0)
		return (ft_error("cd", *(cmd->prog_args + 1), strerror(errno)));
	exit_code = change_pwd(find_env_elem("PWD", env->en_list));
	g_sig.status = exit_code;
	return (1);
}
