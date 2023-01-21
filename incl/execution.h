/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:33:41 by tperes            #+#    #+#             */
/*   Updated: 2023/01/21 12:09:25 by tperes           ###   ########.fr       */
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
# include <signal.h>

# include "libft.h"
# include "struct.h"
# include "builtins.h"

	/*exec.c*/
int		exec(char **av, char *cmd, int fd[2], int fd_in);

int		pipex(t_list *command);

	/*pipe.c*/
int		executing(t_list *command);

int		redir_input(int fdin, t_list *command);
int		redir_output(int tpout, t_list *command);

char	*get_path(char **path, char *cmd);
char	*get_path_cmd(char *cmd);

char	**list_to_tab(t_list *lst);

int		nbr_args(char **av);
int		builtins(int ac, char **av);
int		ifbuiltins(char **av);
int		builtins_parent(int ac, char **av, int fd[2], int fd_in);

void	piping(int fd[2], int fd_in);

char	*file_to_execute(char *cmd);

void	free_tab(char **tab);

#endif
