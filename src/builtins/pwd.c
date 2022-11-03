/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:38:27 by tperes            #+#    #+#             */
/*   Updated: 2022/11/02 15:38:34 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/* TODO
- variable env
- lien symbolique
*/
int	pwd(int ac)
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
