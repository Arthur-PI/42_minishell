/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:50:12 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/02 09:29:00 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	print_tokens(t_list *tokens)
{
	t_token	*token;

	while (tokens)
	{
		token = tokens->content;
		printf("Token: value->%s, type->%d\n", token->value, token->type);
		tokens = tokens->next;
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
