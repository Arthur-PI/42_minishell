/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 09:27:51 by apigeon           #+#    #+#             */
/*   Updated: 2022/10/30 10:53:20 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

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

void	handle_signals(void)
{
	struct sigaction	sa;

	remove_hotkeys();
	sa.sa_handler = &sighandler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(4);
	}
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(5);
	}
}
