/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 09:27:51 by apigeon           #+#    #+#             */
/*   Updated: 2022/12/11 14:22:42 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

t_minishell	g_minishell;

static void	sighandler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sighandler_heredoc(int signum)
{
	(void)signum;
	printf("\n");
	close(STDIN_FILENO);
	g_minishell.signal = 1;
}

void	handle_signals(void)
{
	signal(SIGINT, &sighandler);
	signal(SIGQUIT, SIG_IGN);
	g_minishell.signal = 0;
}

void	handle_signals_heredoc(void)
{
	signal(SIGINT, &sighandler_heredoc);
}
