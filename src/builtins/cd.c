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

#include "minishell.h"

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
			return (print_error("cd: HOME not set", NULL, NULL), 1);
	}
	else if (ac > 2)
		return (print_error("cd: too many arguments", NULL, NULL), 1);
	else if (ac == 2)
	{
		if (chdir(av[1]) == -1)
		{
			print_error("cd: %s: No such file or directory", av[1], NULL);
			return (1);
		}
	}
	g_minishell.exit_status = 0;
	return (0);
}
