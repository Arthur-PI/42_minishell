/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:44:10 by apigeon           #+#    #+#             */
/*   Updated: 2022/12/10 17:59:12 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	lst_remove_quotes(t_list *lst)
{
	t_token	*token;

	while (lst)
	{
		token = lst->content;
		remove_quotes(token->value);
		lst = lst->next;
	}
}

// TODO handle all mallocs
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

// TODO handle all mallocs
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
		if (!quote && (s[i] == ' ' || s[i + 1] == 0))
		{
			if (start != i)
				extract_word(s, start, i, &new);
			start = i + 1;
		}
	}
	if (i == 0)
		extract_word(s, 0, 0, &new);
	return (new);
}

// TODO leaks on replace_envs return assigment
// TODO split the new value in TOKEN_WORD
// TODO protect malloc everywhere
void	lst_expand_var(t_list *lst)
{
	t_list	*new;
	t_list	*last;
	t_token	*token;

	while (lst)
	{
		token = lst->content;
		if (token->type == TOKEN_WORD)
		{
			token->value = replace_envs(token->value);
			new = split_token(token->value);
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
		}
		lst = lst->next;
	}
}
