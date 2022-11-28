/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:13:42 by tperes            #+#    #+#             */
/*   Updated: 2022/11/22 21:19:27 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// TODO Norme
// TODO free -> invalid read of size 8 3x (main et ft_delete) comme pour my_env
// ADVICE faire une fonction qui prends un char* et te redonne l'env qui correspond
// dans la t_list d'envs (qui est dans g_minishell je le rappelle). Comme ca t'as
// juste a recup l'env avec la fonction, le delete et passer au suivant.
// et en plus moi j'aurais bien besoin de cette fonction 👉👈
// ADVICE faire une fonction qui prend un t_env* et le free
// TODO FIX utiliser g_minishell au lieu de se passer l'arg lst
t_list	*ft_delete(t_list *lst, char **av)
{
	t_list	*lst_new;
	t_env	*env;
	int		i;

	lst_new = NULL;
	while (lst != NULL)
	{
		env = lst->content;
		i = 1;
		while (av[i])
		{
			// TODO FIX pas besoin strncmp, strcmp est plus simple ici
			// et en plus du coup pas besoin de la 2eme partie du if
			if (ft_strncmp(av[i], env->name, ft_strlen(env->name)) == 0
				&& ft_strlen(av[i]) == ft_strlen(env->name))
			{
				free(env->name);
				free(env->value);
				free(env);
				free(lst);
				lst = lst->next;
				if (lst == NULL)
					break ;
				env = lst->content;
			}
			i++;
		}
		if (lst == NULL)
			break ;
		ft_lstadd_back(&lst_new, ft_lstnew(env));
		free(lst);
		lst = lst->next;
	}
	return (lst_new);
}

t_list	*my_unset(int ac, char **av, t_list *lst)
{
	t_list	*lst_new;

	lst_new = NULL;
	if (ac > 1)
		lst_new = ft_delete(lst, av);
	return (lst_new);
}
