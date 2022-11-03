/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:35:44 by tperes            #+#    #+#             */
/*   Updated: 2022/11/03 15:38:05 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
- env -> prints the environment variables
TODO free et lstclear
TODO norm
*/

int	my_env(int ac, char **av, char **env)
{
	int		i;
	int		j;
	t_env	*envi;

	i = 0;
	envi = malloc(sizeof(t_env));
	if (envi == NULL)
		return (0);
	envi->list = NULL;
	if (ac == 1)
	{
		while (env[i])
		{
			envi->tab = ft_split(env[i], '=');
			j = 0;
			while (envi->tab[j])
			{	
				if (j == 0)
					envi->name = envi->tab[j];
				else if (j == 1)
					envi->value = envi->tab[j];
				j++;
			}
			ft_lstadd_back(&envi->list, ft_lstnew(envi));
			printf("%s\n", env[i]);
			i++;
		}
	}
	return (0);
}

// Fonction 1: char** -> t_list de t_env
// Fonction 2: affiche tout ce qu'il y a dans la t_list de t_env
// Fonction 3: on creer et ajoute un t_env a la t_list
// Fonction 4: on supprime un t_env de la t_list
// Fonction 5: t_list -> char **
