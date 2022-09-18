/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:06:28 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 15:35:29 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_sig	g_sig;

static void	handle_sigint(int signum)
{
	if (signum != SIGINT)
		return ;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	g_sig.status = 1;
}

static void	hellpp(int argc, char **argv)
{
	(void)(argc);
	(void)(argv);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*g_list;
	t_main	mi;

	g_list = NULL;
	hellpp(argc, argv);
	init_s(&mi, envp);
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		mi.str = readline("mcorneli$ ");
		if (!mi.str)
		{
			clear_t_main(&mi);
			printf("exit\n");
			exit(0);
		}
		add_history(mi.str);
		g_list = get_lexer(mi.str);
		mi.head = g_list;
		mi.curr = g_list;
		start_parse(&g_list, &mi);
		mi.str = NULL;
	}
	return (0);
}
