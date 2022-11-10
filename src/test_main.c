/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:04:44 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/10 15:42:28 by tperes           ###   ########.fr       */
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

int	test_env(int ac, char **av, char **env)
{
	t_list	*lst;
	t_env	*envs;


	lst = tab_to_list(env);
	my_export(ac, av, lst);
	while (lst != NULL)
	{
		envs = lst->content;
		printf("%s=%s\n", envs->name, envs->value);
		lst = lst->next;
	}
	return (my_export(ac, av, lst));
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	test_env(ac, av, env);
	return (0);
}
