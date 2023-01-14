/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:54:55 by tperes            #+#    #+#             */
/*   Updated: 2023/01/09 17:51:24 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

extern t_minishell	g_minishell;

static int	echo_newline(char **av)
{
	int	i;

	if (av[1][0] == '-')
	{
		i = 1;
		while (av[1][i])
		{
			if (av[1][i] != 'n')
				return (false);
			i++;
		}
		return (i > 1);
	}
	return (false);
}

int	echo(int ac, char **av)
{
	int	i;
	int	newline_option;

	i = 1;
	newline_option = false;
	if (ac > 1)
	{
		newline_option = echo_newline(av);
		if (newline_option || ft_strcmp(av[1], "-") == 0)
			i++;
	}
	while (i < ac)
	{
		ft_printf("%s", av[i]);
		i++;
		if (i != ac)
			printf(" ");
	}
	if (!newline_option)
		ft_printf("\n");
	g_minishell.exit_status = 0;
	return (0);
}
