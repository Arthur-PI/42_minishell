/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:33:41 by tperes            #+#    #+#             */
/*   Updated: 2022/12/14 15:47:14 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "minishell.h"
# include "builtins.h"
# include "parser.h"
# include "libft.h"


	/*exec.c*/
int		exec(char **av, char *cmd);

	/*pipe.c*/
int		pipex(int fdin, int tpout, int ret, t_list *command);
int		executing(t_list *command);
#endif
