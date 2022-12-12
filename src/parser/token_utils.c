/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:04:17 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/26 22:52:02 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*get_token_name(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return (ft_strdup("PIPE\t"));
	else if (type == TOKEN_RD_IN)
		return (ft_strdup("RD_IN\t"));
	else if (type == TOKEN_RD_OUT)
		return (ft_strdup("RD_OUT\t"));
	else if (type == TOKEN_RD_APPEND)
		return (ft_strdup("RD_APPEND"));
	else if (type == TOKEN_RD_HEREDOC)
		return (ft_strdup("RD_HEREDOC"));
	else if (type == TOKEN_WORD)
		return (ft_strdup("WORD\t"));
	return (ft_strdup("NONE\t"));
}

void	print_tokens(t_list *tokens)
{
	char	*type;
	t_token	*token;

	while (tokens)
	{
		token = tokens->content;
		type = get_token_name(token->type);
		printf("Token: %s->\t%s\n", type, token->value);
		tokens = tokens->next;
		free(type);
	}
}

t_token_type	get_token_type(char *token_value)
{
	if (ft_strcmp(token_value, "|") == 0)
		return (TOKEN_PIPE);
	else if (ft_strcmp(token_value, "<") == 0)
		return (TOKEN_RD_IN);
	else if (ft_strcmp(token_value, ">") == 0)
		return (TOKEN_RD_OUT);
	else if (ft_strcmp(token_value, "<<") == 0)
		return (TOKEN_RD_HEREDOC);
	else if (ft_strcmp(token_value, ">>") == 0)
		return (TOKEN_RD_APPEND);
	return (TOKEN_WORD);
}

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*token;

	if (value == NULL)
		return (NULL);
	token = malloc(sizeof(*token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	return (token);
}

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}
