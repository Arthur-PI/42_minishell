/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:50:12 by apigeon           #+#    #+#             */
/*   Updated: 2022/12/12 17:11:54 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_token(void *ptr)
{
	t_token	*token;

	token = ptr;
	if (token)
	{
		free(token->value);
		free(token);
	}
}

/* TODO make an exit function that clear g_minishell
 * TODO parse tokens to commands
 * TODO exit with proper exit function
 * TODO exec command
 */
void	*parse_line(char *line)
{
	t_list	*tokens;
	t_list	*commands;

	tokens = get_tokens(line);
	if (!tokens)
		exit(2);
	lst_expand_var(tokens);
	lst_remove_quotes(tokens);
	print_tokens(tokens);
	if (valid_syntax(tokens))
	{
		commands = tokens_to_commands(tokens);
		if (commands)
		{
		//	print_commands(commands);
			pipex(commands);
		}
		ft_lstclear(&commands, &free_command);
	}
	ft_lstclear(&tokens, &free_token);
	return (NULL);
}
