/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:54:55 by tperes            #+#    #+#             */
/*   Updated: 2022/10/25 15:08:56 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/echo.h"

void	echo_newline(t_var *var, char **av)
{
	int	o;

	o = 1;
	while (av[1][0] == '-' && av[1][o])
	{
		var->newline = 0;
		var->i = 2;
		if (av[1][o] != 'n')
		{
			var->newline = 1;
			var->i = 1;
			break ;
		}
		o++;
	}
}

int	echo(int ac, char **av)
{
	t_var	var;

	var.i = 1;
	var.newline = 1;
	if (ac > 1)
	{
		echo_newline(&var, av);
		if (av[1][0] == '-' && !av[1][1])
			var.i = 2;
	}
	while (var.i < ac)
	{
		printf("%s", av[var.i]);
		var.i++;
		if (var.i != ac)
			printf(" ");
	}
	if (var.newline == 1)
		printf("\n");
	return (0);
}
/*
int	main(int ac, char **av)
{
	echo(ac, av);
	return (0);
}*/
