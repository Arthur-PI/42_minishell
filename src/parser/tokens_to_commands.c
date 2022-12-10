/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 21:48:03 by apigeon           #+#    #+#             */
/*   Updated: 2022/12/10 21:48:30 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// TODO deal with malloc protection
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

static t_command	*create_command(t_token *token)
{
	t_command	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	if (token)
		cmd->cmd = ft_strdup(token->value);
	cmd->args = NULL;
	cmd->redirects = NULL;
	return (cmd);
}

static t_redirect_type	get_redirection_type(t_token_type type)
{
	if (type == TOKEN_RD_IN)
		return (RD_IN);
	else if (type == TOKEN_RD_OUT)
		return (RD_OUT);
	else if (type == TOKEN_RD_APPEND)
		return (RD_APPEND);
	else
		return (RD_HEREDOC);
}

static void	add_redirect(t_command *cmd, t_list *rd_type, t_list *file)
{
	t_redirect	*rd;

	rd = malloc(sizeof(*rd));
	rd->file = ft_strdup(((t_token *)file->content)->value);
	rd->type = get_redirection_type(((t_token *) rd_type)->type);
	rd->fd = 1;
	ft_lstadd_back(&cmd->redirects, ft_lstnew(rd));
}

t_list	*tokens_to_commands(t_list *tokens)
{
	t_list		*commands;
	t_token		*token;
	t_command	*command;

	command = NULL;
	commands = NULL;
	while (tokens)
	{
		token = tokens->content;
		if (token->type == TOKEN_WORD)
		{
			if (command == NULL)
				command = create_command(token);
			else if (command->cmd == NULL)
				command->cmd = ft_strdup(token->value);
			string_array_add(&command->args, token->value);
		}
		else if (token->type == TOKEN_PIPE)
		{
			ft_lstadd_back(&commands, ft_lstnew(command));
			command = NULL;
		}
		else
		{
			if (command == NULL)
				command = create_command(NULL);
			if (token->type == TOKEN_RD_OUT || token->type == TOKEN_RD_APPEND
				|| commands == NULL)
				add_redirect(command, tokens, tokens->next);
			else
				add_redirect(commands->content, tokens, tokens->next);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	if (command)
		ft_lstadd_back(&commands, ft_lstnew(command));
	return (commands);
}
