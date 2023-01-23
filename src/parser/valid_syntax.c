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

#include "minishell.h"

extern t_minishell	g_minishell;

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

static void	print_syntax_error(t_list *lst)
{
	char	*token_value;
	t_token	*token;

	token_value = "newline";
	if (lst)
	{
		token = lst->content;
		token_value = token->value;
	}
	print_error("syntax error near unexpected token `%s'", token_value, NULL);
	g_minishell.exit_status = 2;
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
				return (print_syntax_error(tokens), false);
			previous = false;
		}
		else if (is_token_redirect(token->type))
		{
			if (!is_next_word(tokens))
				return (print_syntax_error(tokens->next), false);
			previous = true;
		}
		if (token->type == TOKEN_WORD)
			previous = true;
		tokens = tokens->next;
	}
	return (true);
}
