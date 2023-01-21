/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_open_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:48:59 by apigeon           #+#    #+#             */
/*   Updated: 2023/01/20 12:02:04 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	handle_open_error(const char *s, int type)
{
	if ((type == RD_IN && access(s, F_OK)) || (is_rdout(type) && s[0] == 0))
		printf("minishell: %s: No such file or directory\n", s);
	else if (type == RD_IN && access(s, R_OK))
		printf("minishell: %s: Permission denied\n", s);
	else if (is_rdout(type) && access(s, F_OK) == 0 && access(s, W_OK) != 0)
		printf("minishell: %s: Permission denied\n", s);
	else if (is_rdout(type) && is_directory(s))
		printf("minishell: %s: Is a directory\n", s);
	else
		return (0);
	return (1);
}
