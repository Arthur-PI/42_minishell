/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:54:55 by tperes            #+#    #+#             */
/*   Updated: 2023/01/23 15:30:45 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

static int	echo_newline(char **av, int j)
{
	int	i;

	if (av[j][0] == '-')
	{
		i = 1;
		while (av[j][i])
		{
			if (av[j][i] != 'n')
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
	while (av[i])
	{
		newline_option = echo_newline(av, i);
		if (!newline_option)
			break ;
		i++;
	}
	if (i != 1)
		newline_option = 1;
	while (i < ac)
	{
		ft_printf("%s", av[i]);
		i++;
		if (i != ac)
			ft_printf(" ");
	}
	if (!newline_option)
		ft_printf("\n");
	g_minishell.exit_status = 0;
	return (0);
}
