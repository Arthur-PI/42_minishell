/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:47:15 by tperes            #+#    #+#             */
/*   Updated: 2023/01/06 15:40:46 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern t_minishell	g_minishell;

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
	{
		g_minishell.exit_status = 1;
		return (printf("cd: too many arguments: %s\n", av[1]), 1);
	}
	else if (ac == 2)
	{
		if (chdir(av[1]) == -1)
		{
			printf("cd: no such file or directory: %s\n", av[1]);
			g_minishell.exit_status = 1;
			return (1);
		}
	}
	g_minishell.exit_status = 0;
	return (0);
}
