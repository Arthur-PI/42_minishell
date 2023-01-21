/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:50:12 by apigeon           #+#    #+#             */
/*   Updated: 2023/01/21 12:50:18 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

extern t_minishell	g_minishell;

void	free_token(void *ptr)
{
	t_token	*token;

	token = ptr;
	if (token)
	{
		free(token->value);
		free(token);
	}
}

void	lst_remove_empty(t_list **lst)
{
	t_list	*tokens;
	t_list	*prev;
	t_token	*token;

	prev = NULL;
	tokens = *lst;
	while (tokens)
	{
		token = tokens->content;
		if (token->value && token->value[0] == 0)
		{
			if (prev)
				prev->next = tokens->next;
			else
				*lst = tokens->next;
			free_token(token);
			free(tokens);
		}
		else
			prev = tokens;
		if (prev)
			tokens = prev->next;
		else
			tokens = *lst;
	}
}

t_list	*parse_line(char *line)
{
	t_list	*tokens;
	t_list	*commands;

	tokens = get_tokens(line);
	if (!tokens)
		return (NULL);
	if (lst_expand_var(tokens) == -1)
		return (ft_lstclear(&tokens, &free_token), NULL);
	lst_remove_empty(&tokens);
	if (lst_remove_quotes(tokens) == -1)
		return (ft_lstclear(&tokens, &free_token), NULL);
	if (!valid_syntax(tokens))
		return (ft_lstclear(&tokens, &free_token), NULL);
	commands = tokens_to_commands(tokens);
	g_minishell.commands = commands;
	ft_lstclear(&tokens, &free_token);
	return (commands);
}
