/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:04:44 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/28 21:39:22 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	test_pipe(int ac, char **av)
{
	char	*line;

	(void)ac;
	(void)av;
	line = "/usr/bin/ls -l | /usr/bin/grep tea | /usr/bin/wc -l";
	pipex(line);
	return (0);
}

/*
int	test_env(int ac, char **av, char **env)
{
	t_list	*lst;

	lst = tab_to_list(env);
	return (my_env(ac, av, my_export(ac, av)));
}
*/

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
	test_pipe(ac, av);
	return (0);
}
