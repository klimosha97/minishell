/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcorneli <mcorneli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:09:22 by mcorneli          #+#    #+#             */
/*   Updated: 2022/09/18 14:09:23 by mcorneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*find_env_elem(char *name, t_list *lst)
{
	while (lst)
	{
		if (ft_strncmp(name, lst->key, ft_strlen(name) + 1) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

int	get_keys_in_envp_lst(t_list *lst, char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=')
		i++;
	lst->key = malloc(sizeof(char) * i + 1);
	if (!lst->key)
		exit(EXIT_FAILURE);
	ft_strlcpy(lst->key, src, i + 1);
	if (!src[i])
	{
		lst->value = NULL;
		return (0);
	}
	i++;
	if (!src[i])
	{
		lst->value = ft_strdup("");
		return (0);
	}
	lst->value = (char *) malloc(sizeof(char) * ft_strlen(&src[i]) + 1);
	if (!lst->value)
		exit(EXIT_FAILURE);
	ft_strlcpy(lst->value, &src[i], ft_strlen(&src[i]) + 1);
	return (0);
}

void	create_envp_list(char **envp, t_env *env)
{
	t_list	*new;

	env->en_list = NULL;
	env->my_env = NULL;
	env->size = 0;
	env->env = envp;
	while (envp[env->size])
	{
		new = ft_lstnew(-2);
		get_keys_in_envp_lst(new, envp[env->size]);
		ft_lstadd_back(&env->en_list, new);
		env->size++;
	}
}

static void	copy_env_lst(char *dst, t_list *env)
{
	int	i;

	i = -1;
	while (env->key[++i])
		dst[i] = env->key[i];
	dst[i++] = '=';
	ft_strlcpy(&dst[i], env->value, ft_strlen(env->value) + 1);
}

void	create_envp_arr(t_env *env)
{
	int		i;
	t_list	*start;

	start = env->en_list;
	env->my_env = (char **)malloc(sizeof(char *) * env->size);
	if (!env->my_env)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < env->size)
	{
		env->my_env[i] = (char *) malloc(sizeof(char)
				* (ft_strlen(start->key) + ft_strlen(start->value)) + 2);
		copy_env_lst(env->my_env[i], start);
		i++;
		start = start->next;
	}
}
