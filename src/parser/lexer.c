/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:27:40 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/01 12:36:16 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_strndup(char *src, int len)
{
	int		i;
	char	*new;

	new = malloc(len + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (src[i] && i < len)
	{
		new[i] = src[i];
		i++;
	}
	new[i] = 0;
	return (new);
}

int	get_token_type(char *token_value)
{
	if (ft_strcmp(token_value, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(token_value, "<") == 0)
		return (REDIRECT_INPUT);
	else if (ft_strcmp(token_value, ">") == 0)
		return (REDIRECT_OUTPUT);
	else if (ft_strcmp(token_value, "<<") == 0)
		return (REDIRECT_HEREDOC);
	else if (ft_strcmp(token_value, ">>") == 0)
		return (REDIRECT_APPEND);
	return (WORD);
}

t_list	*extract_token(char *line, int start, int end)
{
	t_list	*el;
	t_token	*token;

	token = malloc(sizeof(*token));
	token->value = ft_strndup(line + start, end - start);
	token->type = get_token_type(token->value);
	el = ft_lstnew(token);
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

	lst = NULL;
	i = 0;
	while (line[i])
	{
		start = i;
		while (line[i] && !ft_isspace(line[i]))
			i = skip_quote(line, i);
		end = i;
		ft_lstadd_back(&lst, extract_token(line, start, end));
		while (ft_isspace(line[i]))
			i++;
	}
	return (lst);
}
