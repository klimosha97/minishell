/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:52:05 by                   #+#    #+#             */
/*   Updated: 2021/10/16 15:52:05 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast(*lst);
	new->prev = tmp;
	tmp->next = new;
}

void	ft_lstadd_back_cmd(t_cmdinfo **cmd, t_cmdinfo *new)
{
	t_cmdinfo	*tmp;

	if (*cmd == NULL)
	{
		*cmd = new;
		return ;
	}
	tmp = ft_lstlast_cmd(*cmd);
	new->prev = tmp;
	tmp->next = new;
}
