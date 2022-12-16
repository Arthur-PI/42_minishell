/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:44:10 by apigeon           #+#    #+#             */
/*   Updated: 2022/12/15 21:24:35 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	extract_word(const char *s, uint start, uint end, t_list **new)
{
	t_list	*tmp;
	t_token	*token;
	char	*word;

	if (s[end] && s[end + 1] == 0)
		end++;
	word = ft_substr(s, start, end - start);
	token = new_token(word, TOKEN_WORD);
	tmp = ft_lstnew(token);
	ft_lstadd_back(new, tmp);
}

static t_list	*split_token(char *s)
{
	uint	i;
	uint	start;
	t_list	*new;
	char	quote;

	i = -1;
	quote = 0;
	start = 0;
	new = NULL;
	while (s[++i])
	{
		if (is_quote(s[i]) && quote == 0)
			quote = s[i];
		else if (is_quote(s[i]) && s[i] == quote)
			quote = 0;
		if (!quote && s[i] == ' ')
		{
			if (start != i)
				extract_word(s, start, i, &new);
			start = i + 1;
		}
	}
	extract_word(s, start, i, &new);
	return (new);
}

static int	split_words(t_list *lst)
{
	t_list	*new;
	t_list	*last;
	t_token	*token;

	token = lst->content;
	new = split_token(token->value);
	if (!new)
		return (-1);
	free_token(lst->content);
	lst->content = new->content;
	last = ft_lstlast(new);
	last->next = lst->next;
	if (last != new)
	{
		lst->next = new->next;
		lst = last;
	}
	free(new);
	return (1);
}

int	lst_expand_var(t_list *lst)
{
	t_token	*token;

	while (lst)
	{
		token = lst->content;
		if (token->type == TOKEN_WORD)
		{
			token->value = replace_envs(token->value);
			if (!token->value)
				return (-1);
			if (split_words(lst) == -1)
				return (-1);
		}
		lst = lst->next;
	}
	return (1);
}
