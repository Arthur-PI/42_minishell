/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:35:44 by tperes            #+#    #+#             */
/*   Updated: 2022/11/05 12:16:40 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/* TODO free et lstclear
 * TODO norm
 */
t_env	*create_env(char *env)
{
	t_env	*new_env;
	int		i;
	int		j;

	i = 0;
	new_env = malloc(sizeof(*new_env));
	if (!new_env)
		return (NULL);
	while (env[i] != '=')
		i++;
	new_env->name = ft_substr(env, 0, i);
	i++;
	j = i;
	while (env[j])
		j++;
	new_env->value = ft_substr(env, i, j - i);
	return (new_env);
}

t_list	*tab_to_list(char **env)
{
	t_list	*lst_env;
	int		i;

	i = 0;
	lst_env = NULL;
	while (env[i])
	{
		ft_lstadd_back(&lst_env, ft_lstnew(create_env(env[i])));
		i++;
	}
	return (lst_env);
}

int	my_env(int ac, char **av, t_list *lst)
{
	t_env	*env;

	if (ac == 1)
	{
		while (lst != NULL)
		{
			env = lst->content;
			printf("%s=%s\n", env->name, env->value);
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
