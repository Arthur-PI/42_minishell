/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:08:12 by tperes            #+#    #+#             */
/*   Updated: 2022/11/10 15:47:47 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
TODO export test test
TODO export ::=12 -> export: not valid in this context: ::
TODO export !! -> bizarre
TODO export ;; -> syntax error neat unexpected token ';;'
TODO trop de trucs chiants 
*/

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
			if (av[i][0] > '0' && av[i][0] < '9')
			{
				printf("export: not an identifier: %s\n", av[i]);
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
