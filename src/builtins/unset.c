/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:13:42 by tperes            #+#    #+#             */
/*   Updated: 2022/12/12 23:06:06 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern t_minishell	g_minishell;

// TODO Norme
// TODO free -> invalid read of size 8 3x (main et ft_delete) comme pour my_env
// TODO FIX -> je comprends mais je pense juste que tu comprends mal
// comment fonctionne strcmp et c'est pour ca, j'explique discord
t_env	*get_env_el(char *av)
{
	t_env	*envs;
	t_list	*lst;

	envs = NULL;
	lst = g_minishell.envs;
	while (lst != NULL)
	{
		envs = lst->content;
		if (ft_strncmp(av, envs->name, ft_strlen(envs->name)) == 0
			&& ft_strlen(av) == ft_strlen(envs->name))
			return (envs);
		lst = lst->next;
	}
	return (envs);
}

t_list	*ft_delete(char *av)
{
	t_env	*env;
	t_list	*lst;
	t_list	*lst_new;

	lst = g_minishell.envs;
	lst_new = NULL;
	while (lst != NULL)
	{
		env = lst->content;
		if (env == get_env_el(av))
		{
			lst = lst->next;
			if (!lst)
				break ;
			env = lst->content;
		}
		if (!lst)
			break ;
		ft_lstadd_back(&lst_new, ft_lstnew(env));
		lst = lst->next;
	}
	return (lst_new);
}

// TODO fonction qui check les arguments de unset
static char	*print_name(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '=')
		i++;
	av[i] = '\0';
	printf("unset: %s: invalid parameter name\n", av);
	return (av);
}

static int	check_arg(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] < '0')
			return (print_name(av), 0);
		else if (av[i] > '9' && av[i] < 'A')
			return (print_name(av), 0);
		else if (av[i] > 'Z' && av[i] < '_')
			return (print_name(av), 0);
		else if (av[i] > '_' && av[i] < 'a')
			return (print_name(av), 0);
		else if (av[i] > 'z')
			return (print_name(av), 0);
		else
			i++;
	}
	return (1);
}

// FIXED ? pareil que pour export, si check_arg est faux
// tu vas delete celui d'apres sans le checker. Un else
int	my_unset(int ac, char **av)
{
	int	i;

	i = 1;
//	g_minishell.envs = tab_to_list(env);
	if (ac > 1)
	{
		while (av[i])
		{
			if (!check_arg(av[i]))
			{
				if (av[i + 1])
					i++;
				else
					break ;
			}
			else
				g_minishell.envs = ft_delete(av[i]);
			i++;
		}
	}
	return (0);
}
