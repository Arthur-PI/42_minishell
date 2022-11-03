/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:04:44 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/03 19:56:55 by tperes           ###   ########.fr       */
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

	lst = tab_to_list(env);
	return (my_env(ac, av, my_export(ac, av)));
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	test_env(ac, av, env);
	return (0);
}
