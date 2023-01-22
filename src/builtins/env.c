/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:35:44 by tperes            #+#    #+#             */
/*   Updated: 2023/01/21 11:36:40 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern t_minishell	g_minishell;

void	free_env(void *ptr)
{
	t_env	*env;

	env = ptr;
	if (env)
	{
		free(env->name);
		free(env->value);
		free(env);
	}
}

t_env	*create_env(char *env)
{
	int		i;
	int		j;
	t_env	*new_env;

	i = 0;
	new_env = malloc(sizeof(*new_env));
	if (!new_env)
		return (NULL);
	while (env[i] != '=')
		i++;
	new_env->name = ft_substr(env, 0, i);
	if (new_env->name == NULL)
		return (free(new_env), NULL);
	i++;
	j = i;
	while (env[j])
		j++;
	new_env->value = ft_substr(env, i, j - i);
	if (new_env->value == NULL)
		return (free(new_env->name), free(new_env), NULL);
	return (new_env);
}

t_list	*add_env(t_list *lst, char *env)
{
	t_list	*new;
	t_env	*envs;
	t_env	*old;

	envs = create_env(env);
	if (envs == NULL)
		exit(12);
	old = get_env_el(envs->name);
	if (old)
	{
		if (old->value)
			free(old->value);
		old->value = envs->value;
		return (free(envs->name), free(envs), lst);
	}
	new = ft_lstnew(envs);
	if (new == NULL)
	{
		free_env(envs);
		ft_lstclear(&lst, &free_env);
		exit(12);
	}
	ft_lstadd_back(&lst, new);
	return (lst);
}

t_list	*tab_to_list(char **env)
{
	int		i;
	t_list	*lst_env;

	i = 0;
	lst_env = NULL;
	while (env[i])
	{
		lst_env = add_env(lst_env, env[i]);
		i++;
	}
	return (lst_env);
}

int	my_env(int ac, char **av)
{
	t_env	*envs;
	t_list	*lst;

	(void)av;
	lst = g_minishell.envs;
	if (ac == 1)
	{
		while (lst != NULL)
		{
			envs = lst->content;
			if (envs->value)
				printf("%s=%s\n", envs->name, envs->value);
			lst = lst->next;
		}
	}
	g_minishell.exit_status = 0;
	return (0);
}
