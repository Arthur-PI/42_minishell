/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:20:25 by apigeon           #+#    #+#             */
/*   Updated: 2023/01/06 08:59:58 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "builtins.h"
# include "parser.h"
# include "execution.h"
# include "utils.h"

typedef struct s_minishell
{
	int		signal;
	int		exit_status;
	t_list	*envs;
}				t_minishell;

void	handle_signals(void);
void	handle_signals_heredoc(void);

#endif
