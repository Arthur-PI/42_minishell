/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:20:54 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/26 22:49:50 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

void	usage(char *prog_name)
{
	printf("%s: too many arguments\n", prog_name);
}

/* TODO make an exit function that free what is in g_minishell
 */
char	*get_line(void)
{
	char	*line;
	char	*prompt;

	prompt = "minishell->";
	line = readline(prompt);
	if (!line)
		exit(1);
	else if (*line)
		add_history(line);
	return (line);
}

/* TODO exec commands
 * TODO free commands if not NULL
 */
void	routine(void)
{
	char	*line;
	t_list	*commands;

	(void)commands;
	while (1)
	{
		line = get_line();
		commands = parse_line(line);
		free(line);
	}
}

/* TODO Extract and format the envp variables in a t_list
 * TODO Deal with error on envp transformation
 */
int	main(int ac, char **av, char **envp)
{	
	if (ac > 1)
		return (usage(av[0]), 1);
	g_minishell.envs = tab_to_list(envp);
	if (envp && envp[0] && !g_minishell.envs)
		return (1);
	handle_signals();
	routine();
	return (0);
}
