/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:04:17 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/11 00:36:26 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

char	*remove_quotes(char *s)
{
	int		i;
	int		nb_quotes;
	char	current_quote;

	i = 0;
	nb_quotes = 0;
	current_quote = 0;
	while (s[i])
	{
		if (is_quote(s[i]) && current_quote == 0)
		{
			nb_quotes++;
			current_quote = s[i];
		}
		else if (s[i] == current_quote)
		{
			nb_quotes++;
			current_quote = 0;
		}
		else
			s[i - nb_quotes] = s[i];
		i++;
	}
	s[i - nb_quotes] = s[i];
	return (s);
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

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}
