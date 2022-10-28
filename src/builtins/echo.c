/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 14:54:55 by tperes            #+#    #+#             */
/*   Updated: 2022/10/28 18:10:50 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	echo_newline(t_var *var, char **av)
{
	int	o;

	o = 1;
	while (av[1][0] == '-' && av[1][o])
	{
		var->newline = false;
		var->i = 2;
		if (av[1][o] != 'n')
		{
			var->newline = true;
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
	var.newline = true;
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
	if (var.newline == true)
		printf("\n");
	return (0);
}
