/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:04:44 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/29 19:09:49 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "parser.h"
#include <string.h>

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
	t_list	*lst;
	
	lst = tab_to_list(env);
	my_env(ac, av, lst);
	return (0);
}

int	test_export(int ac, char **av, char **env)
{
	t_list	*lst;
	
	(void)env;
	lst = tab_to_list(env);
	my_export(ac, av, lst);
	return (0);
}

int	test_unset(int ac, char **av, char **env)
{
	t_list	*list;
	t_env	*envs;

	list = my_unset(ac, av, tab_to_list(env));
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
