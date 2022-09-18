/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:52:07 by                   #+#    #+#             */
/*   Updated: 2021/12/27 15:22:51 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	if (*lst)
		(*lst)->prev = new;
	*lst = new;
}

t_list	*get_head(t_list *lst)
{
	while (lst && lst->prev != NULL)
		lst = lst->prev;
	return (lst);
}
