/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:35:44 by tperes            #+#    #+#             */
/*   Updated: 2022/11/30 10:48:37 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

extern t_minishell	g_minishell;
/* TODO invalid read of size 8 avec free(lst) ligne 75
 * TODO norme
 */

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

// FIXED ? ft_substr peut return NULL (free new_env)
// FIXED ? ft_substr peut return NULL (free new_env et new_env->name)

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

// FIXED ? ft_lstnew peut return NULL, a gerer (exit proprement et free lst_env)
// FIXED ? pareil pour create_env, peut return NULL, a gerer proprement
t_list	*add_env(t_list *lst, char *env)
{
	t_list	*new;
	t_env	*envs;

	envs = create_env(env);
	new = ft_lstnew(envs);
	ft_lstadd_back(&lst, new);
	if (envs == NULL || new == NULL)
	{
		free_env(envs);
		ft_lstclear(&lst, &free_env);
		exit(1);
	}
	return (lst);
}

t_list	*tab_to_list(char **env)
{
	t_list	*lst_env;
	int		i;

	i = 0;
	lst_env = NULL;
	while (env[i])
	{
		lst_env = add_env(lst_env, env[i]);
		i++;
	}
	return (lst_env);
}

// FIXED ? pas besoin de l'arg t_list *lst pcq normalement
// les env sont dans g_minishell->envs
int	my_env(int ac, char **av, char **env)
{
	t_env	*envs;
	t_list	*lst;

	(void)av;
	g_minishell.envs = tab_to_list(env);
	lst = g_minishell.envs;
	if (ac == 1)
	{
		while (lst != NULL)
		{
			envs = lst->content;
			printf("%s=%s\n", envs->name, envs->value);
			free_env(envs);
			lst = lst->next;
		}
	}
	return (0);
}

// Fonction 1: char** -> t_list de t_env
// Fonction 2: affiche tout ce qu'il y a dans la t_list de t_env
// Fonction 3: on cree et ajoute un t_env a la t_list
// Fonction 4: on supprime un t_env de la t_list
// Fonction 5: t_list -> char **
