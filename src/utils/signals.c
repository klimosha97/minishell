/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:09:36 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 15:29:00 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_sigint_change(int signum)
{
	if (signum != SIGINT)
		return ;
	write(1, "\n", 1);
}

static void	handle_sigquit_change(int signum)
{
	if (signum != SIGQUIT)
		return ;
}

void	change_signal(void)
{
	signal(SIGINT, handle_sigint_change);
	signal(SIGQUIT, handle_sigquit_change);
}

void	set_exit_code(int status)
{
	if (WIFEXITED(status))
		g_sig.status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_sig.status = 128 + WTERMSIG(status);
		if (g_sig.status == 131)
			ft_putendl_fd("Quit: 3", STDERR_FILENO);
	}
	else
		g_sig.status = EXIT_FAILURE;
}
