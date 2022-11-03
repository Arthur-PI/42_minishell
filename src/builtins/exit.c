/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:09:07 by tperes            #+#    #+#             */
/*   Updated: 2022/11/03 15:38:43 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

/*tests essayes

- exit
- exit 12
- exit 12 12 (trouver un bon main pour mieux tester les valeurs de retour)
- exit aa
- exit aa aa
- exit 0
 - only one '-' or one '+' and n whitspaces before and after for the atoi
 - take care of values below 0 and above 255
 - take care of values above max int and max long
*/

static int	char_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	atoi_exit(const char *str)
{
	int		i;
	int		sign;
	long	n;

	i = 0;
	while (char_isspace(str[i]))
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
/*
int	main(int ac, char **av)
{
	char	*line;
	int		i;

	i = 0;
	while (i < 5)
	{
		line = get_next_line(0);
		printf("%s", line);
		i++;
		free(line);
		my_exit(ac, av);
	}
	return (0);
}*/
