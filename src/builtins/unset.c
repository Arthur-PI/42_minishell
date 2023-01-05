/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:13:42 by tperes            #+#    #+#             */
/*   Updated: 2023/01/03 14:37:48 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern t_minishell	g_minishell;

t_env	*get_env_el(char *av)
{
	t_env	*envs;
	t_list	*lst;

	envs = NULL;
	lst = g_minishell.envs;
	while (lst != NULL)
	{
		envs = lst->content;
		if (ft_strncmp(av, envs->name, ft_strlen(envs->name)) == 0
			&& ft_strlen(av) == ft_strlen(envs->name))
			return (envs);
		lst = lst->next;
	}
	return (NULL);
}

t_list	*ft_delete(char *av)
{
	t_env	*env;
	t_list	*lst;
	t_list	*lst_new;

	lst = g_minishell.envs;
	lst_new = NULL;
	while (lst != NULL)
	{
		env = lst->content;
		if (env == get_env_el(av))
		{
			lst = lst->next;
			if (!lst)
				break ;
			env = lst->content;
		}
		if (!lst)
			break ;
		ft_lstadd_back(&lst_new, ft_lstnew(env));
		lst = lst->next;
	}
	return (lst_new);
}

static int	check_arg(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] == '=')
			return (0);
		if (av[i] < '0')
			return (0);
		else if (av[i] > '9' && av[i] < 'A')
			return (0);
		else if (av[i] > 'Z' && av[i] < '_')
			return (0);
		else if (av[i] > '_' && av[i] < 'a')
			return (0);
		else if (av[i] > 'z')
			return (0);
		else
			i++;
	}
	return (1);
}

int	my_unset(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac > 1)
	{
		while (av[i])
		{
			if (check_arg(av[i]))
				g_minishell.envs = ft_delete(av[i]);
			i++;
		}
	}
	return (0);
}
