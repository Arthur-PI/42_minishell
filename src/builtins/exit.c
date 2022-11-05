/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:09:07 by tperes            #+#    #+#             */
/*   Updated: 2022/11/03 19:00:26 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
			exit(2);
		}
		status = atoi_exit(av[1]);
	}
	while (ac > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	exit(status);
}
