/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:20:54 by apigeon           #+#    #+#             */
/*   Updated: 2023/01/21 14:43:35 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(const char *format, const char *arg1, const char *arg2)
{
	int	save;

	save = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("minishell: ");
	if (arg2)
		printf(format, arg1, arg2);
	else if (arg1)
		printf(format, arg1);
	else
		printf("%s", format);
	printf("\n");
	dup2(save, STDOUT_FILENO);
	close(save);
}
