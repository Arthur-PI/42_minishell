/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:33:41 by tperes            #+#    #+#             */
/*   Updated: 2023/01/10 16:15:24 by tperes           ###   ########.fr       */
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

# include "libft.h"
# include "struct.h"
# include "builtins.h"

	/*exec.c*/
int		exec(char **av, char *cmd);

	/*pipe.c*/
int		pipex(int fdin, int tpout, int ret, t_list *command);
int		executing(t_list *command);

int		redir_input(int fdin, t_list *command);
int		redir_output(int tpout, t_list *command);

char	*get_path(char **path, char *cmd);
char	*get_path_cmd(char *cmd);

#endif
