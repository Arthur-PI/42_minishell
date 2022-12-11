/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:20:25 by apigeon           #+#    #+#             */
/*   Updated: 2022/12/11 14:19:51 by apigeon          ###   ########.fr       */
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
# include "utils.h"

typedef struct s_minishell
{
	int		signal;
	t_list	*envs;
}				t_minishell;

void	handle_signals(void);
void	handle_signals_heredoc(void);

#endif
