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
#include <signal.h>

extern t_minishell	g_minishell;

static void	sighandler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_minishell.exit_status = 1;
}

static void	sighandler_heredoc(int signum)
{
	(void)signum;
	printf("\n");
	g_minishell.exit_status = 1;
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

void	handle_signals_heredoc_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
