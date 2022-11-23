/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:08:12 by tperes            #+#    #+#             */
/*   Updated: 2022/11/22 21:25:17 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	valid_name(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '=')
	{
		if (av[0] > '0' && av[0] < '9')
		{
			while (av[i] != '=')
				i++;
			av[i] = '\0';
			printf("export: not an identifier: %s\n", av);
			return (0);
		}
		if ((av[i] < '0') || (av[i] > '9' && av[i] < 'A')
			|| (av[i] > 'Z' && av[i] < '_')
			|| (av[i] > '_' && av[i] < 'a') || (av[i] > 'z'))
		{
			while (av[i] != '=')
				i++;
			av[i] = '\0';
			printf("export: not valid in this context: %s\n", av);
			return (0);
		}
		i++;
	}
	return (1);
}

//TODO export test test

int	my_export(int ac, char **av, t_list *lst)
{
	int	i;

	i = 1;
	if (ac == 1)
	{
		my_env(ac, av, lst);
		return (0);
	}
	else if (ac > 1)
	{
		while (av[i])
		{
			if (valid_name(av[i]) == 0)
			{
				if (av[i + 1])
					i++;
				else
					break ;
			}
			ft_lstadd_back(&lst, ft_lstnew(create_env(av[i])));
			i++;
		}
	}
	return (0);
}
