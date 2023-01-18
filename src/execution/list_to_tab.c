/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:59:39 by apigeon           #+#    #+#             */
/*   Updated: 2022/12/16 18:38:15 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**list_to_tab(t_list *lst)
{
	uint	i;
	t_env	*env;
	char	*s;
	char	*tmp;
	char	**tab;

	i = 0;
	tab = malloc((ft_lstsize(lst) + 1) * sizeof(*tab));
	if (!tab)
		exit(12);
	while (lst)
	{
		env = lst->content;
		tmp = ft_strjoin(env->name, "=");
		s = ft_strjoin(tmp, env->value);
		free(tmp);
		tab[i++] = s;
		lst = lst->next;
	}
	tab[i] = NULL;
	return (tab);
}
