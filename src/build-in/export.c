/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:07:39 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 14:07:41 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_export_env(t_list *env)
{
	t_list	*start;

	start = env;
	while (start)
	{
		printf("declare -x %s", start->key);
		if (start->value)
			printf("=\"%s\"", (char *)start->value);
		printf("\n");
		start = start->next;
	}
}

static void	change_env_elem(t_list *lst, char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=')
		i++;
	if (!src[i] && !src[i + 1])
		return ;
	free(lst->value);
	i++;
	lst->value = NULL;
	lst->value = (char *) malloc(sizeof(char ) * ft_strlen(&src[i]) + 1);
	if (!lst->value)
		exit(EXIT_FAILURE);
	ft_strlcpy(lst->value, &src[i], ft_strlen(&src[i]) + 1);
}

static char	*get_name(const char *src)
{
	int		i;
	char	*name;

	i = 0;
	while (src[i] && src[i] != '=')
		i++;
	name = malloc(sizeof(char) * i + 1);
	if (!name)
		exit(EXIT_FAILURE);
	ft_strlcpy(name, src, i + 1);
	return (name);
}

static int	export_kernel(t_cmdinfo *cmd, t_main *mi, t_list *new, char *name)
{
	int	i;

	i = 0;
	while (++i < cmd->size_args)
	{
		name = get_name(cmd->prog_args[i]);
		new = find_env_elem(name, mi->my_env->en_list);
		free(name);
		if (new == NULL)
		{
			new = ft_lstnew(-2);
			if (get_keys_in_envp_lst(new, cmd->prog_args[i]))
			{
				free(new);
				g_sig.status = 1;
				return (error_env("export", cmd->prog_args[i]));
			}
			ft_lstadd_back(&mi->my_env->en_list, new);
			mi->my_env->size++;
		}
		else
			change_env_elem(new, cmd->prog_args[i]);
	}
	g_sig.status = 0;
	return (0);
}

int	build_export(t_cmdinfo *cmd, t_main *mi)
{
	if (cmd->size_args == 1)
	{
		print_export_env(mi->my_env->en_list);
		g_sig.status = 0;
		return (0);
	}
	return (export_kernel(cmd, mi, NULL, NULL));
}
