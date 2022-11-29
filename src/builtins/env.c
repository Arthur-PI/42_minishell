/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:35:44 by tperes            #+#    #+#             */
/*   Updated: 2022/11/29 15:10:30 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
	// TODO FIX ft_substr peut return NULL (free new_env)
	new_env->name = ft_substr(env, 0, i);
	if (ft_substr(env, 0, i) == NULL)
		return (free(new_env), NULL);
	i++;
	j = i;
	while (env[j])
		j++;
	// TODO FIX ft_substr peut return NULL (free new_env et new_env->name)
	new_env->value = ft_substr(env, i, j - i);
	if (ft_substr(env, 0, i) == NULL)
		return (free(new_env->name), free(new_env), NULL);
	return (new_env);
}

// TODO FIX: Pk ya 2 args ???? 1 c'etait tres bien
t_list	*tab_to_list(char **env, char **av)
{
	t_list	*lst_env;
	int		i;

	i = 0;
	lst_env = NULL;
	while (env[i])
	{
		// TODO FIX ft_lstnew peut return NULL, a gerer (exit proprement et free lst_env)
		// TODO FIX pareil pour create_env, peut return NULL, a gerer proprement
		ft_lstadd_back(&lst_env, ft_lstnew(create_env(env[i])));
		i++;
	}
	i = 1;
	while (av[i])
	{
		// TODO FIX ft_lstnew peut return NULL, a gerer (exit proprement et free lst_env)
		// TODO FIX pareil pour create_env, peut return NULL, a gerer proprement
		ft_lstadd_back(&lst_env, ft_lstnew(create_env(av[i])));
		i++;
	}
	return (lst_env);
}

// TODO FIX pas besoin de l'arg t_list *lst pcq normalement
// les env sont dans g_minishell->envs
// TODO FIX pk cette fonction free les envs ??? faire une fonction a par qui fait ca
int	my_env(int ac, char **av, t_list *lst)
{
	t_env	*env;

	(void)av;
	if (ac == 1)
	{
		while (lst != NULL)
		{
			env = lst->content;
			printf("%s=%s\n", env->name, env->value);
		//	free(env->name);
		//	free(env->value);
		//	free(env);
		//	free(lst);
			ft_lstdelone(lst, &free_env);
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
