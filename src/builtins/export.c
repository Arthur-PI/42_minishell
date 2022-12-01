/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:08:12 by tperes            #+#    #+#             */
/*   Updated: 2022/12/01 15:43:05 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

extern t_minishell	g_minishell;

// ADVICE faire une fonction qui check si un charactere est
// valide pour un name au lieu d'avoir un if a ralonge

static char	*print_name(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '=')
		i++;
	av[i] = '\0';
	return (av);
}

static int	check_char(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '=')
	{
		if (av[i] < '0')
			return (0);
		else if (av[i] > '9' && av[i] < 'A')
			return (0);
		else if (av[i] > 'Z' && av[i] < '_')
			return (0);
		else if (av[i] > '_' && av[i] < 'a')
			return (0);
		else if (av[i] > 'z')
			return (0);
		else
			i++;
	}
	return (1);
}

int	valid_name(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '=')
	{
		if (av[0] > '0' && av[0] < '9')
		{
			av = print_name(av);
			printf("export: not an identifier: %s\n", av);
			return (0);
		}
		if (!check_char(av))
		{
			av = print_name(av);
			printf("export: not valid in this context: %s\n", av);
			return (0);
		}
		i++;
	}
	return (1);
}

// TODO export test test
// FIXED ? encore une fois pas besoin de t_list *lst
int	my_export(int ac, char **av, char **env)
{
	int		i;
	t_list	*lst;

	lst = g_minishell.envs;
	if (ac == 1)
		return (my_env(ac, av, env));
	else
	{
		i = 1;
		while (av[i])
		{
			if (valid_name(av[i]) == 0)
			{
				if (av[i + 1])
					i++;
				else
					break ;
			}
			g_minishell.envs = add_env(lst, av[i]);
			i++;
		}
	}
	return (0);
}
