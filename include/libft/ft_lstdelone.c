/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:52:12 by                   #+#    #+#             */
/*   Updated: 2021/10/17 04:26:26 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstdelone(t_list *lst)
{
	if (!lst)
		return ;
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
	if (lst->key)
		free(lst->key);
	if (lst->value)
		free(lst->value);
	free(lst);
	lst = NULL;
}

static void	clean_double_char(char **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

void	ft_lstdelone_cmd(t_cmdinfo *lst)
{
	if (!lst)
		return ;
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
	if (lst->prog_args)
		clean_double_char(lst->prog_args, lst->size_args);
	if (lst->file_in)
		free(lst->file_in);
	if (lst->file_out)
		free(lst->file_out);
	if (lst->delim)
		free(lst->delim);
	free(lst);
	lst = NULL;
}
