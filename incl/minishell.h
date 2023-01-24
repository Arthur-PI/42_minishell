/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:20:25 by apigeon           #+#    #+#             */
/*   Updated: 2023/01/09 17:54:21 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "builtins.h"
# include "parser.h"
# include "execution.h"
# include "struct.h"

char	*readinput(const char *prompt);
void	handle_signals(void);
void	handle_signals_exec(void);
void	handle_signals_heredoc(void);
void	reset_signals(void);
void	print_error(const char *format, const char *arg1, const char *arg2);

#endif
