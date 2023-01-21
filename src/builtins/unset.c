/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:13:42 by tperes            #+#    #+#             */
/*   Updated: 2023/01/21 14:35:01 by tperes           ###   ########.fr       */
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

t_list	*ft_delete(t_list *lst, t_env *del_env, char *av)
{
	t_env	*env;
	t_list	*lst_new;
	t_list	*tmp;

	lst_new = NULL;
	while (lst != NULL)
	{
		env = lst->content;
		if (ft_strncmp(av, env->name, ft_strlen(env->name) + 1) == 0)
		{
			del_env = env;
			tmp = lst;
			lst = lst->next;
			free(tmp);
			continue ;
		}
		ft_lstadd_back(&lst_new, ft_lstnew(env));
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	if (del_env)
		free_env(del_env);
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
	int		i;
	t_list	*lst;
	t_env	*del_env;

	i = 1;
	del_env = NULL;
	lst = g_minishell.envs;
	if (ac > 1)
	{
		while (av[i])
		{
			if (i > 1)
				lst = g_minishell.envs;
			if (check_arg(av[i]))
				g_minishell.envs = ft_delete(lst, del_env, av[i]);
			i++;
		}
	}
	g_minishell.exit_status = 0;
	return (0);
}
