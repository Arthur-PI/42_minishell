/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 21:48:03 by apigeon           #+#    #+#             */
/*   Updated: 2022/12/16 18:38:32 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	string_array_add(char ***array, char *s)
{
	uint	i;
	uint	len;
	char	**new;

	len = 0;
	while (*array && (*array)[len])
		len++;
	new = malloc((len + 2) * sizeof(*new));
	i = 0;
	while (i < len)
	{
		new[i] = (*array)[i];
		i++;
	}
	new[i] = ft_strdup(s);
	new[i + 1] = NULL;
	if (*array)
		free(*array);
	*array = new;
}

static int	process_word(t_token *token, t_command **command_addr)
{
	t_command	*command;

	if (token->type == TOKEN_WORD)
	{
		command = *command_addr;
		if (*command_addr == NULL)
			*command_addr = create_command(token);
		else if (command->cmd == NULL)
			command->cmd = ft_strdup(token->value);
		command = *command_addr;
		string_array_add(&command->args, token->value);
	}
	return (1);
}

static int	process_pipe(t_token *token, t_list **commands, t_command *command)
{
	if (token->type == TOKEN_PIPE)
	{
		ft_lstadd_back(commands, ft_lstnew(command));
		command = NULL;
	}
	return (1);
}

t_list	*tokens_to_commands(t_list *tokens)
{
	t_list		*commands;
	t_command	*command;

	command = NULL;
	commands = NULL;
	while (tokens)
	{
		if (process_word(tokens->content, &command) == -1)
			return (NULL);
		if (process_pipe(tokens->content, &commands, command) == -1)
			return (NULL);
		if (process_rd(tokens->content, &command, &tokens) == -1)
			return (NULL);
		tokens = tokens->next;
	}
	if (command)
		ft_lstadd_back(&commands, ft_lstnew(command));
	return (commands);
}
