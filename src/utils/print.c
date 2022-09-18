/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:09:31 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 14:09:32 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_double_char(char **str, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		printf("%s\n", *str);
		str++;
		i++;
	}
	return (1);
}

void	print_cmds(t_cmdinfo *cmds)
{
	int	i;

	i = -1;
	while (cmds)
	{
		printf("type = %d\nsize_args = %d\nfile in = %s\nfile out = %s\ndelim = "
			"%s\nsize pipe = %d\nchmod = %d\n\nARGUMENTS\n", cmds->type,
			cmds->size_args, cmds->file_in, cmds->file_out, cmds->delim,
			cmds->size_pipes, cmds->chmod);
		while (++i < cmds->size_args)
			printf("%s\n", cmds->prog_args[i]);
		printf("--------------------------------------------------------\n");
		i = -1;
		cmds = cmds->next;
	}
}

void	print_lex_list(t_list *lex)
{
	t_list	*start;

	start = lex;
	while (start)
	{
		printf("%s=%s\n", start->key, (char *)start->value);
		start = start->next;
	}
}

void	print_env_list(t_list *env)
{
	t_list	*start;

	start = env;
	while (start)
	{
		printf("%s=%s\n", start->key, (char *)start->value);
		start = start->next;
	}
}
