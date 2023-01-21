/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:08:12 by tperes            #+#    #+#             */
/*   Updated: 2023/01/17 20:33:25 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern t_minishell	g_minishell;

static char	*print_name1(char *av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	av[i] = '\0';
	printf("export: not an identifier: %s\n", av);
	return (av);
}

static int	check_char(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] == '=')
			break ;
		if (av[i] < '0')
			return (0);
		else if (av[i] > '9' && av[i] < '=')
			return (0);
		else if (av[i] > '=' && av[i] < 'A')
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
	while (av[i])
	{
		if (av[0] == '=')
			return (print_name1(av), 1);
		if ((av[0] > '0' && av[0] < '9') || !check_char(av))
		{
			printf("minishell: export: `%s': not a valid identifier\n", av);
			return (1);
		}
		i++;
	}
	if (ft_strchr(av, '=') == NULL)
		return (2);
	return (0);
}

int	my_export(int ac, char **av)
{
	int		i;
	int		ret;
	int		valid;
	t_list	*lst;

	lst = g_minishell.envs;
	ret = 0;
	if (ac == 1)
		return (my_env(ac, av));
	i = 1;
	while (av[i])
	{
		valid = valid_name(av[i]);
		if (valid == 0)
			g_minishell.envs = add_env(lst, av[i]);
		else if (valid == 2 && ret == 0)
			ret = 0;
		else
			ret = 1;
		i++;
	}
	g_minishell.exit_status = ret;
	return (ret);
}
