/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:20:54 by apigeon           #+#    #+#             */
/*   Updated: 2022/10/30 10:54:03 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	usage(char *prog_name)
{
	printf("%s: too many arguments\n", prog_name);
	return (1);
}

/*
 * TODO parse input and get the right struct
 * TODO exec input with the parsed line
 * TODO free the structure of the parsed line
 * */
int	main(int ac, char **av)
{
	char	*line;
	char	*prompt;

	if (ac > 1)
		return (usage(av[0]));
	handle_signals();
	prompt = "minishell->";
	while (1)
	{
		line = readline(prompt);
		if (!line)
			exit(2);
		if (*line)
			add_history(line);
		free(line);
	}
	rl_clear_history();
	return (0);
}
