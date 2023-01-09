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
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "builtins.h"
# include "parser.h"
# include "execution.h"
# include "struct.h"

void	handle_signals(void);
void	handle_signals_heredoc(void);

#endif
