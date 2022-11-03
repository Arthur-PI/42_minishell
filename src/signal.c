/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 09:27:51 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/02 10:25:08 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sighandler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
// TODO save the termios_old setup to global variable to reset config
static void	remove_hotkeys(void)
{
	int				err;
	struct termios	termios_old;
	struct termios	termios_new;

	err = tcgetattr(0, &termios_old);
	if (err)
	{
		perror("tcgetattr");
		exit(1);
	}
	termios_new = termios_old;
	termios_new.c_lflag &= ~ECHOCTL;
	err = tcsetattr(0, 0, &termios_new);
	if (err)
	{
		perror("tcsetattr");
		exit(1);
	}
}
*/

void	handle_signals(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
}
