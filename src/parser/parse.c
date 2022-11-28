/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:50:12 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/26 22:52:44 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

/* TODO make an exit function that clear g_minishell
 * TODO parse tokens to commands
 */
void	*parse_line(char *line)
{
	t_list	*tokens;

	tokens = get_tokens(line);
	if (!tokens)
		exit(2);
	lst_remove_quotes(tokens);
	print_tokens(tokens);
	ft_lstclear(&tokens, &free_token);
	return (NULL);
}
