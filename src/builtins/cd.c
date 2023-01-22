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

char	*get_home(void)
{
	t_env	*env;
	char	*home;

	home = NULL;
	env = get_env_el("HOME");
	if (env && env->value)
		home = env->value;
	return (home);
}

int	cd(int ac, char **av)
{
	char	*home;

	g_minishell.exit_status = 1;
	if (ac == 1)
	{
		home = get_home();
		if (home && chdir(home) == -1)
			return (1);
		else if (!home)
			return (printf("minishell: cd: HOME not set\n"), 1);
	}
	else if (ac > 2)
		return (printf("minishell: cd: too many arguments\n"), 1);
	else if (ac == 2)
	{
		if (chdir(av[1]) == -1)
		{
			printf("minishell: cd: %s: No such file or directory\n", av[1]);
			return (1);
		}
	}
	g_minishell.exit_status = 0;
	return (0);
}
