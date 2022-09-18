/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:09:27 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 14:09:28 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_s(t_main *mi, char **envp)
{
	mi->str = NULL;
	mi->head = NULL;
	mi->curr = NULL;
	mi->my_env = malloc(sizeof(t_env));
	if (!mi->my_env)
		exit(EXIT_FAILURE);
	create_envp_list(envp, mi->my_env);
}

void	clear_t_main(t_main *mi)
{
	if (mi->str)
		free(mi->str);
	if (!mi->my_env)
		return ;
	if (mi->my_env->en_list)
		clear_t_list(mi->my_env->en_list);
	if (mi->my_env->my_env)
		clean_double_char(mi->my_env->my_env, mi->my_env->size);
	free(mi->my_env);
}
