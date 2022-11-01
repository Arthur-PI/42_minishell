/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:04:44 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/01 14:29:07 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	test_echo(int ac, char **av)
{
	return (echo(ac, av));
}

int	test_pwd(int ac)
{
	return (pwd(ac));
}

int	test_exit(int ac, char **av)
{
	my_exit(ac, av);
	ft_printf("%s\n", "ok");
	return (0);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	test_echo(ac, av);
	return (0);
}
