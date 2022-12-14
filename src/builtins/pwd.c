/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:38:27 by tperes            #+#    #+#             */
/*   Updated: 2023/01/06 15:06:29 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

extern t_minishell	g_minishell;
/* TODO
- variable env
- lien symbolique
*/
int	pwd(int ac)
{
	char	buf[MAXPATHLEN];

	(void)ac;
	if (getcwd(buf, sizeof(buf)) == NULL)
		return (0);
	printf("%s\n", buf);
	g_minishell.exit_status = 0;
	return (0);
}
