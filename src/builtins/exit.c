/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:09:07 by tperes            #+#    #+#             */
/*   Updated: 2023/01/22 18:22:07 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

static long	atoi_exit(const char *str)
{
	int			i;
	int			sign;
	long long	n;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	n = 0;
	while (str[i])
	{
		n = n * 10 + str[i] - '0';
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (n * sign);
}

static void	free_exit(int status)
{
	ft_lstclear(&g_minishell.envs, free_env);
	ft_lstclear((t_list **)&g_minishell.commands, &free_command);
	exit(status);
}

static bool	is_valid(char **av)
{
	int	sign;

	sign = (av[1][0] == '-' || av[1][0] == '+');
	if ((size_t)(19 + sign) < ft_strlen(av[1]))
		return (false);
	if (av[1][0] != '-' && ft_strcmp(av[1] + sign, "9223372036854775808") >= 0)
		return (false);
	if (av[1][0] == '-' && ft_strcmp(av[1] + 1, "9223372036854775808") > 0)
		return (false);
	return (true);
}

static bool	verif_number(char **av)
{
	int	i;

	i = 0;
	if (av[1][i] == '-' || av[1][i] == '+')
		i++;
	while (av[1][i])
	{
		if (ft_isdigit(av[1][i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

int	my_exit(int ac, char **av)
{
	int		status;
	long	value;

	printf("exit\n");
	status = g_minishell.exit_status;
	if (ac > 1)
	{
		value = atoi_exit(av[1]);
		if (!verif_number(av) || !is_valid(av))
		{
			printf("minishell: exit: %s: numeric argument required\n", av[1]);
			free_exit(2);
		}
		status = value;
	}
	if (ac > 2)
	{
		printf("minishell: exit: too many arguments\n");
		g_minishell.exit_status = 1;
		return (1);
	}
	free_exit(status);
	exit(status);
}
