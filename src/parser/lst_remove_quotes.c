/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_remove_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 22:13:31 by apigeon           #+#    #+#             */
/*   Updated: 2022/12/16 13:32:46 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	is_quotes_valid(const char *s)
{
	char	quote;
	uint	i;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			if (quote == 0)
				quote = s[i];
			else if (s[i] == quote)
				quote = 0;
		}
		i++;
	}
	return (quote == 0);
}

int	lst_remove_quotes(t_list *lst)
{
	t_token	*token;

	while (lst)
	{
		token = lst->content;
		if (!is_quotes_valid(token->value))
		{
			printf("minishell: unclosed quote\n");
			return (-1);
		}
		remove_quotes(token->value);
		lst = lst->next;
	}
	return (1);
}
