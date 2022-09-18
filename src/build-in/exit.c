/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:07:24 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 14:07:33 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_lld(unsigned long long res, int sign)
{
	if (res > 9223372036854775807UL && sign > 0)
		return (0);
	if (res > 9223372036854775808UL && sign < 0)
		return (0);
	return (1);
}

int	valid_exit_code(const char *s)
{
	char				*ptr;
	unsigned long long	res;
	int					sign;

	ptr = (char *)s;
	res = 0;
	sign = 1;
	if (*ptr == '-')
	{
		sign = -1;
		ptr++;
	}
	while (*ptr)
	{
		if (res > res * 10 + (*ptr - '0'))
			return (0);
		res = res * 10 + (*ptr - '0');
		ptr++;
	}
	return (check_lld(res, sign));
}

unsigned char	check_exit_arg(char *arg)
{
	char	*tmp;

	tmp = arg;
	if (*tmp == '-')
		tmp++;
	while (*tmp)
	{
		if (!ft_isdigit(*tmp))
		{
			ft_error("exit", tmp, "numeric argument required");
			exit(255);
		}
		tmp++;
	}
	if (valid_exit_code(arg) == 0)
	{
		ft_error("exit", tmp, "numeric argument required");
		exit(255);
	}
	return (ft_atoi(arg));
}

int	ft_exit(char **prog_args, t_main *mi, t_cmdinfo *cmd)
{
	unsigned char	exit_code;

	exit_code = EXIT_SUCCESS;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (*(prog_args + 1))
	{
		exit_code = check_exit_arg(*(prog_args + 1));
		if (*(prog_args + 2))
			ft_error("exit", NULL, "too many arguments");
	}
	clear_t_main(mi);
	clear_t_cmdlist(cmd);
	exit(exit_code);
}
