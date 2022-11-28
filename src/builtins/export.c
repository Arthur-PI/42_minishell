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
		// ADVICE faire une fonction qui check si un charactere est
		// valide pour un name au lieu d'avoir un if a ralonge
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

// TODO export test test
// TODO FIX encore une fois pas besoin de t_list *lst
int	my_export(int ac, char **av, t_list *lst)
{
	int	i;

	if (ac == 1)
	{
		my_env(ac, av, lst);
		return (0);
	}
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
			// TODO FIX ft_lstnew peut return NULL, a gerer (bien tout free)
			// TODO FIX create_env peut return NULL, a gerer (bien tout free)
			// ADVICE comme c'est la meme chose que dans tab_to_list() je te conseille
			// de faire une fonction qui creer l'env l'element de la list et l'ajoute
			// a la lst tout en gerant les erreurs ca fera d'une pierre 2 coups
			ft_lstadd_back(&lst, ft_lstnew(create_env(av[i])));
			i++;
		}
	}
	return (0);
}
