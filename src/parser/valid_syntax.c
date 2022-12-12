/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 21:40:40 by apigeon           #+#    #+#             */
/*   Updated: 2022/12/11 19:58:30 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_token_redirect(t_token_type type)
{
	if (type == TOKEN_RD_OUT)
		return (true);
	if (type == TOKEN_RD_APPEND)
		return (true);
	if (type == TOKEN_RD_IN)
		return (true);
	if (type == TOKEN_RD_HEREDOC)
		return (true);
	return (false);
}

static int	is_next_word(t_list *tokens)
{
	t_token	*token;

	tokens = tokens->next;
	token = NULL;
	if (tokens)
		token = tokens->content;
	if (!tokens || token->type != TOKEN_WORD)
		return (false);
	return (true);
}

int	valid_syntax(t_list *tokens)
{
	int		previous;
	t_token	*token;

	previous = false;
	while (tokens)
	{
		token = tokens->content;
		if (token->type == TOKEN_PIPE)
		{
			if (!previous)
				return (false);
			previous = false;
		}
		else if (is_token_redirect(token->type))
		{
			if (!is_next_word(tokens))
				return (false);
			previous = true;
		}
		if (token->type == TOKEN_WORD)
			previous = true;
		tokens = tokens->next;
	}
	return (true);
}
