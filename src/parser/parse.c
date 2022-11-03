/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:50:12 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/03 11:17:34 by apigeon          ###   ########.fr       */
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

static void	print_tokens(t_list *tokens)
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

void	free_token(void *ptr)
{
	t_token	*token;

	token = ptr;
	free(token->value);
	free(token);
}

void	*parse_line(char *line)
{
	t_list	*tokens;

	tokens = get_tokens(line);
	if (!tokens)
		return (NULL);
	print_tokens(tokens);
	ft_lstclear(&tokens, &free_token);
	return (NULL);
}
