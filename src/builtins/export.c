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

#include "minishell.h"

extern t_minishell	g_minishell;

static char	*print_name(char *av)
{
	int	i;

	i = 0;
	while (av[i])
		i++;
	av[i] = '\0';
	print_error("export: `%s': not an identifier", av, NULL);
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

	if (av[0] == '=')
		return (print_name(av), 1);
	i = 0;
	while (av[i])
	{
		if ((av[0] > '0' && av[0] < '9') || !check_char(av))
		{
			print_error("%s: `%s': not a valid identifier", "export", av);
			return (1);
		}
		i++;
	}
	if (ft_strchr(av, '=') == NULL)
		return (2);
	return (0);
}

void	print_envs(t_list *envs)
{
	t_env	*env;

	while (envs)
	{
		env = envs->content;
		printf("export %s", env->name);
		if (env->value)
			printf("=\"%s\"\n", env->value);
		else
			printf("\n");
		envs = envs->next;
	}
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
		print_envs(lst);
	i = 1;
	while (av[i])
	{
		valid = valid_name(av[i]);
		if (valid == 0)
			g_minishell.envs = add_env(lst, av[i]);
		else if (valid == 2)
			g_minishell.envs = add_empty_env(lst, av[i]);
		else
			ret = 1;
		i++;
	}
	g_minishell.exit_status = ret;
	return (ret);
}
