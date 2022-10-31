/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:50:12 by apigeon           #+#    #+#             */
/*   Updated: 2022/10/31 15:01:56 by apigeon          ###   ########.fr       */
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

void	*parse_line(char *line)
{
	t_list	*tokens;

	tokens = get_tokens(line);
	print_tokens(tokens);
	return (NULL);
}
