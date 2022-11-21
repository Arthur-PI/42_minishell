/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:13:42 by tperes            #+#    #+#             */
/*   Updated: 2022/11/15 16:50:43 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//TODO Norme
// TODO free -> invalid read of size 8 3x (main et ft_delete) comme pour my_env

t_list	*ft_delete(t_list *lst, char **av)
{
	t_list	*lst_new;
	t_env	*env;
	int	i;

	lst_new = NULL;
	while (lst != NULL)
	{
		env = lst->content;
		i = 1;
		while (av[i])
		{
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
