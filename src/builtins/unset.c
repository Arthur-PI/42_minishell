/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:13:42 by tperes            #+#    #+#             */
/*   Updated: 2022/12/01 12:15:03 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

extern t_minishell	g_minishell;

// TODO Norme
// TODO free -> invalid read of size 8 3x (main et ft_delete) comme pour my_env
// ADVICE faire une fonction qui prends un char* et te redonne l'env qui correspond
// dans la t_list d'envs (qui est dans g_minishell je le rappelle). Comme ca t'as
// juste a recup l'env avec la fonction, le delete et passer au suivant.
// et en plus moi j'aurais bien besoin de cette fonction 👉👈
// FIXED ? utiliser g_minishell au lieu de se passer l'arg lst

//pas d'accord => FIX pas besoin strncmp, strcmp est plus simple ici
// et en plus du coup pas besoin de la 2eme partie du if

t_env	*get_env_el(char *av)
{
	t_env	*envs;

	while (g_minishell.envs != NULL)
	{
		envs = g_minishell.envs->content;
		if (ft_strncmp(av, envs->name, ft_strlen(envs->name)) == 0
			&& ft_strlen(av) == ft_strlen(envs->name))
			return (envs);
		g_minishell.envs = g_minishell.envs->next;
	}
	return (envs);
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

int	my_unset(int ac, char **av, char **env)
{
	int	i;

	i = 1;
	g_minishell.envs = tab_to_list(env);
	if (ac > 1)
	{
		while (av[i])
		{
			g_minishell.envs = ft_delete(av[i]);
			i++;
		}
	}
	return (0);
}
