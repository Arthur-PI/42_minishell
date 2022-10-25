/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:38:27 by tperes            #+#    #+#             */
/*   Updated: 2022/10/25 15:27:45 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/param.h>

/* TO DO

- variable env
- lien symbolique
*/

int	pwd(int ac, char **av)
{
	char	buf[MAXPATHLEN];

	if (ac != 1)
	{
		printf("pwd: too many arguments\n");
		return (0);
	}
	if (getcwd(buf, sizeof(buf)) == NULL)
		return (0);
	printf("%s\n", buf);
	return (0);
}
/*
int	main(int ac, char **av)
{
	pwd(ac, av);
	return (0);
}*/
