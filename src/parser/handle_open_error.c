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

#include "minishell.h"

int	handle_open_error(const char *s, int type)
{
	if ((type == RD_IN && access(s, F_OK)) || (is_rdout(type) && s[0] == 0))
		print_error("%s: No such file or directory", s, NULL);
	else if (type == RD_IN && access(s, R_OK))
		print_error("%s: Permission denied", s, NULL);
	else if (is_rdout(type) && access(s, F_OK) == 0 && access(s, W_OK) != 0)
		print_error("%s: Permission denied", s, NULL);
	else if (is_rdout(type) && is_directory(s))
		print_error("%s: Is a directory", s, NULL);
	else
		return (0);
	return (1);
}
