/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readinput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:20:54 by apigeon           #+#    #+#             */
/*   Updated: 2023/01/21 14:43:35 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

char	*readinput(const char *prompt)
{
	size_t	last;
	char	*line;

	line = NULL;
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		line = readline(prompt);
	else
	{
		if (isatty(STDIN_FILENO))
			printf("%s", prompt);
		line = get_next_line(STDIN_FILENO);
		if (line)
		{
			last = ft_strlen(line) - 1;
			if (last >= 0 && line[last] == '\n')
				line[last] = 0;
		}
	}
	return (line);
}
