/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:27:40 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/08 09:44:53 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_token	*create_token(char *value)
{
	return (new_token(value, get_token_type(value)));
}

static void	add_token(t_list **lst, char *line, int start, int end)
{
	t_list	*el;
	t_token	*token;

	token = create_token(ft_substr(line, start, end - start));
	if (!token)
		exit(12);
	el = ft_lstnew(token);
	if (!el)
	{
		free_token(token);
		ft_lstclear(lst, &free_token);
		exit(12);
	}
	ft_lstadd_back(lst, el);
}

static int	skip_quote(char *line, int i)
{
	char	quote;

	if (line[i] == '\'' || line[i] == '"')
	{
		quote = line[i];
		i++;
		while (line[i] && line[i] != quote)
			i++;
	}
	if (line[i])
		i++;
	return (i);
}

static int	extract_operator(t_list **lst, char *line, int i)
{
	char	*s;

	s = line + i;
	if (ft_strncmp(s, "<<", 2) == 0 || ft_strncmp(s, ">>", 2) == 0)
	{
		add_token(lst, line, i, i + 2);
		return (i + 2);
	}
	add_token(lst, line, i, i + 1);
	return (i + 1);
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
		while (line[i] && !ft_isspace(line[i]) && !is_operator(line[i]))
			i = skip_quote(line, i);
		end = i;
		if (start != end)
			add_token(&lst, line, start, end);
		if (is_operator(line[i]))
			i = extract_operator(&lst, line, i);
		while (ft_isspace(line[i]))
			i++;
	}
	return (lst);
}
