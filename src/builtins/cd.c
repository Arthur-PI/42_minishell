/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:47:15 by tperes            #+#    #+#             */
/*   Updated: 2022/12/31 09:12:40 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern t_minishell	g_minishell;

/*
- cd with a directory that exists
- cd with a directory that doesn't exist
- cd with many arguments
TODO cd with no argument
*/

char	*home(void)
{
	t_env	*env;
	t_list	*lst;
	char	*home;

	home = NULL;
	lst = g_minishell.envs;
	while (lst != NULL)
	{
		env = lst->content;
		if (env == get_env_el("HOME"))
			home = env->value;
		lst = lst->next;
	}
	return (home);
}

// TODO FIX handle chdir return value in case of error
int	cd(int ac, char **av)
{
	if (ac == 1)
	{
		if (chdir(home()) == -1)
			return (1);
	}
	else if (ac > 2)
		return (printf("cd: string not in pwd: %s\n", av[1]), 1);
	else if (ac == 2)
	{
		if (chdir(av[1]) == -1)
		{
			printf("cd: no such file or directory: %s\n", av[1]);
			return (1);
		}
	}
	return (0);
}
