/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:09:07 by tperes            #+#    #+#             */
/*   Updated: 2023/01/12 16:52:14 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern t_minishell	g_minishell;

static int	atoi_exit(const char *str)
{
	int		i;
	int		sign;
	long	n;

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

int	my_exit(int ac, char **av)
{
	int	status;

	printf("exit\n");
	status = 0;
	if (ac > 1)
	{
		if (atoi_exit(av[1]) == 0 && av[1][0] != '0')
		{
			printf("minishell: exit: %s: numeric argument required\n", av[1]);
			ft_lstclear(&g_minishell.envs, free_env);
			exit(2);
		}
		status = atoi_exit(av[1]);
	}
	while (ac > 2)
	{
		printf("minishell: exit: too many arguments\n");
		g_minishell.exit_status = 1;
		return (1);
	}
	g_minishell.exit_status = status;
	ft_lstclear(&g_minishell.envs, free_env);
	exit(status);
}
