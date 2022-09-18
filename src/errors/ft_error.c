/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:08:04 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 14:08:05 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	error_syntax(int token)
{
	ft_putstr_fd("mcorneli: syntax error near unexpected token `", 2);
	if (token == OR)
		ft_putstr_fd("||", STDERR_FILENO);
	else if (token == AND)
		ft_putstr_fd("&&", STDERR_FILENO);
	else if (token == PIPE)
		ft_putstr_fd("|", STDERR_FILENO);
	else if (token == UMPERS)
		ft_putstr_fd("&", STDERR_FILENO);
	else if (token == DOUBLE_QUOTES)
		ft_putstr_fd("\"", STDERR_FILENO);
	else if (token == SIMICOLON)
		ft_putstr_fd("&", STDERR_FILENO);
	else if (token == REDIR_IN)
		ft_putstr_fd("<", STDERR_FILENO);
	else if (token == REDIR_OUT)
		ft_putstr_fd(">", STDERR_FILENO);
	else if (token == QUOTES)
		ft_putstr_fd("\'", STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	return (1);
}

int	error_env(char *cmd, char *arg)
{
	ft_putstr_fd("mcorneli: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("`", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("\': not a valid identifier\n", STDERR_FILENO);
	return (1);
}

int	error_usage(char *cmd, char *argv)
{
	ft_putstr_fd("mcorneli: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	write(STDERR_FILENO, argv, ft_strlen(argv));
	ft_putstr_fd(": invalid option\n", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": usage: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}

int	ft_error(char *cmd, char *args, char *error)
{
	ft_putstr_fd("mcorneli: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (args)
	{
		ft_putstr_fd(args, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}
