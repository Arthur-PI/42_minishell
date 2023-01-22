/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_empty_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:08:12 by tperes            #+#    #+#             */
/*   Updated: 2023/01/17 20:33:25 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_list	*add_empty_env(t_list *lst, char *s)
{
	t_env	*env;
	t_list	*new;

	env = malloc(sizeof(*env));
	if (!env)
		exit(12);
	env->name = ft_strdup(s);
	if (!env->name)
		exit(12);
	env->value = NULL;
	new = ft_lstnew(env);
	if (!new)
		exit(12);
	ft_lstadd_back(&lst, new);
	return (lst);
}
