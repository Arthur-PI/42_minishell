/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:47:15 by tperes            #+#    #+#             */
/*   Updated: 2023/01/16 17:24:10 by tperes           ###   ########.fr       */
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
		return (printf(" too many arguments\n"), 1);
	}
	else if (ac == 2)
	{
		if (chdir(av[1]) == -1)
		{
			printf("minishell: cd: %s: No such file or directory\n", av[1]);
			g_minishell.exit_status = 1;
			return (1);
		}
	}
	g_minishell.exit_status = 0;
	return (0);
}
