/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:20:54 by apigeon           #+#    #+#             */
/*   Updated: 2023/01/09 12:02:33 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "libft.h"
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

/* TODO exec commands
 * TODO free commands if not NULL
 */
static void	routine(void)
{
	char	*line;
	t_list	*commands;

	while (1)
	{
		line = get_line();
		if (!line)
			break ;
		commands = parse_line(line);
		free(line);
		if (!commands)
			break ;
		executing(commands);
	//	ft_lstclear(&commands, &free_command);
	}
	ft_lstclear(&g_minishell.envs, free_env);
}

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
