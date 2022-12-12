/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:18:02 by tperes            #+#    #+#             */
/*   Updated: 2022/12/09 13:49:35 by tperes           ###   ########.fr       */
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

int	test_exec(int ac, char **av)
{
	char	*cmd;

	(void)ac;
	cmd = "/usr/bin/ls";
	exec(av, cmd);
	return (0);
}

int	test_pipe(int ac, char **av, char **env)
{
	char	*line;

	(void)ac;
	(void)av;
	g_minishell.envs = tab_to_list(env);
	line = "cat Makefile | wc -l";
	pipex(line);
	return (0);
}

int	test_env(int ac, char **av)
{
	my_env(ac, av);
	return (0);
}

int	test_export(int ac, char **av, char **env)
{
	t_env	*envs;

//	g_minishell.envs = tab_to_list(env);
	(void)env;
	my_export(ac, av);
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

	(void)env;
	my_unset(ac, av);
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

int	test_lst_command(void)
{
	int	i;
	t_command	*command;
	t_list	*cmd;
	char	*line;

	line = "ls -l | grep tea | wc -l";
	i = 0;
	cmd = list_cmd(line);
	while (cmd != NULL)
	{
		command = cmd->content;
		printf("cmd_full %s\ncmd %s\n", command->cmd_full, command->cmd);
		while (command->args[i])
		{
			if (command->args[i][0] == '|')
				i++;
			printf("args = %s\n", command->args[i]);
			i++;
		}
		printf("\n");
		cmd = cmd->next;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	g_minishell.envs = tab_to_list(env);
	test_pipe(ac, av, env);
	return (0);
}

