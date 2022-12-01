/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:04:44 by apigeon           #+#    #+#             */
/*   Updated: 2022/12/01 15:51:09 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "parser.h"
#include <string.h>

t_minishell	g_minishell;

int	test_echo(int ac, char **av)
{
	return (echo(ac, av));
}

int	test_pwd(int ac)
{
	return (pwd(ac));
}

int	test_exit(int ac, char **av)
{
	char	*line;
	int		i;

	i = 0;
	while (i < 5)
	{
		line = get_next_line(0);
		printf("%s", line);
		if (my_exit(ac, av) == 1)
			return (1);
		i++;
		free(line);
	}
	return (my_exit(ac, av));
}

int	test_cd(int ac, char **av)
{
	return (cd(ac, av));
}


int	test_env(int ac, char **av, char **env)
{
	my_env(ac, av, env);
	return (0);
}

int	test_export(int ac, char **av, char **env)
{
	t_env	*envs;

	g_minishell.envs = tab_to_list(env);
	my_export(ac, av, env);
	if (ac > 1)
	{
		while (g_minishell.envs != NULL)
		{
			envs = g_minishell.envs->content;
			printf("%s=%s\n", envs->name, envs->value);
			free_env(envs);
			g_minishell.envs = g_minishell.envs->next;
		}
	}
	return (0);
}

int	test_unset(int ac, char **av, char **env)
{
	t_list	*list;
	t_env	*envs;

	my_unset(ac, av, env);
	list = g_minishell.envs;
	while (list != NULL)
	{
		envs = list->content;
		printf("%s=%s\n", envs->name, envs->value);
		free_env(envs);
		list = list->next;
	}
	return (0);
}

int	test_remove_quotes(int ac, char **av)
{
	char	*s;

	(void)ac;
	(void)av;
	s = strdup("abc\"   Bonj'our\"   def'    P**e des bo\"is, BIIIIM!'");
	remove_quotes(s);
	printf("%s\n", s);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	test_unset(ac, av, env);
	return (0);
}
