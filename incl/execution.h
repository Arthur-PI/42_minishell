/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <tperes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:33:41 by tperes            #+#    #+#             */
/*   Updated: 2022/12/08 18:17:55 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "minishell.h"
# include "builtins.h"
# include "parser.h"
# include "libft.h"


	/*exec.c*/
int		exec(char **av, char *cmd);

	/*pipe.c*/
int		pipex(char *line);

	/*command_utils.c*/
int		nbr_pipes(char *line, char c);
int		start_cmd(char *line, int j);
int		len_cmd(char *line, int j);
void	free_cmd(void *ptr);
t_list	*list_cmd( char *line);
t_list	*add_cmd(t_list *lst, char *line, int i);

#endif
