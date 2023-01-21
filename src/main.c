/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:20:54 by apigeon           #+#    #+#             */
/*   Updated: 2023/01/21 14:43:35 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

static void	usage(char *prog_name)
{
	printf("%s: too many arguments\n", prog_name);
}

/* TODO make an exit function that free what is in g_minishell
 */
static char	*get_line(void)
{
	char	*line;
	char	*prompt;

	prompt = "minishell$ ";
	line = readline(prompt);
	if (!line)
		return (NULL);
	else if (*line)
		add_history(line);
	return (line);
}

static void	routine(void)
{
	char	*line;
	t_list	*commands;

	while (1)
	{
		line = get_line();
		if (!line)
			break ;
		if (!is_empty(line))
		{
			commands = parse_line(line);
			if (commands)
				executing(commands);
			ft_lstclear(&commands, &free_command);
			g_minishell.commands = NULL;
		}
		free(line);
	}
	ft_lstclear(&g_minishell.envs, free_env);
}

static void	init_minishell(char **envp)
{
	g_minishell.envs = tab_to_list(envp);
	if (envp && envp[0] && !g_minishell.envs)
		exit(12);
	g_minishell.signal = 0;
	g_minishell.exit_status = 0;
	g_minishell.commands = NULL;
}

int	main(int ac, char **av, char **envp)
{	
	if (ac > 1)
		return (usage(av[0]), 1);
	init_minishell(envp);
	handle_signals();
	routine();
	return (g_minishell.exit_status);
}
