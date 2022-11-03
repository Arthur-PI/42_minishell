/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:27:40 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/03 19:21:53 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

t_list	*extract_token(char *line, int start, int end)
{
	t_list	*el;
	t_token	*token;

	token = malloc(sizeof(*token));
	if (!token)
		return (NULL);
	token->value = ft_strndup(line + start, end - start);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = get_token_type(token->value);
	el = ft_lstnew(token);
	if (!el)
	{
		free(token->value);
		free(token);
	}
	return (el);
}

int	skip_quote(char *line, int i)
{
	char	quote;

	if (line[i] == '\'' || line[i] == '"')
	{
		quote = line[i];
		i++;
		while (line[i] && line[i] != quote)
			i++;
	}
	i++;
	return (i);
}

t_list	*get_tokens(char *line)
{
	int		i;
	int		start;
	int		end;
	t_list	*lst;
	t_list	*el;

	lst = NULL;
	i = 0;
	while (line[i])
	{
		start = i;
		while (line[i] && !ft_isspace(line[i]))
			i = skip_quote(line, i);
		end = i;
		el = extract_token(line, start, end);
		if (!el)
		{
			ft_lstclear(&lst, &free_token);
			return (NULL);
		}
		ft_lstadd_back(&lst, el);
		while (ft_isspace(line[i]))
			i++;
	}
	return (lst);
}
