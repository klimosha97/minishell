/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:52:19 by                   #+#    #+#             */
/*   Updated: 2021/12/27 00:07:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstnew(int type)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!(new))
		return (NULL);
	new->type = type;
	new->key = NULL;
	new->start = -1;
	new->last = -1;
	new->next = NULL;
	new->prev = NULL;
	new->value = NULL;
	return (new);
}

t_cmdinfo	*ft_lstnew_cmd(void)
{
	t_cmdinfo	*new;

	new = (t_cmdinfo *) malloc(sizeof(t_cmdinfo));
	if (!new)
		return (NULL);
	new->size_args = 0;
	new->type = 0;
	new->prog_args = NULL;
	new->file_in = NULL;
	new->fd_in = -1;
	new->file_out = NULL;
	new->fd_out = -1;
	new->delim = NULL;
	new->size_pipes = 0;
	new->chmod = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
