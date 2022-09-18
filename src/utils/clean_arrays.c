/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_arrays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:09:18 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 14:09:19 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_double_char(char **arr, int size)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (i < size)
	{
		if (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		i++;
	}
	free(arr);
}

void	clear_path_array_int(int **array, int size)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (i < size)
		free(array[i++]);
	free(array);
}

void	clear_t_list(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->key)
			free(head->key);
		if (head->value)
			free(head->value);
		head->prev = NULL;
		head->next = NULL;
		free(head);
		head = tmp;
	}
}

void	clear_group_list(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->key)
		{
			free(head->key);
			head->key = NULL;
		}
		if (head->value)
		{
			clear_t_list(head->value);
			head->value = NULL;
		}
		head->value = NULL;
		head->prev = NULL;
		head->next = NULL;
		free(head);
		head = tmp;
	}
}

void	clear_t_cmdlist(t_cmdinfo *lst)
{
	t_cmdinfo	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		ft_lstdelone_cmd(tmp);
	}
}
