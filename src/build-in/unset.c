/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:07:54 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 14:07:56 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	build_unset(t_cmdinfo *cmd, t_main *mi)
{
	int		i;
	t_list	*tmp;

	i = 1;
	while (i < cmd->size_args)
	{
		tmp = find_env_elem(cmd->prog_args[i], mi->my_env->en_list);
		if (tmp)
		{
			ft_lstdelone(tmp);
			tmp = NULL;
			mi->my_env->size--;
		}
		i++;
	}
	g_sig.status = 0;
	return (0);
}
