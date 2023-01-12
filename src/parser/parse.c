/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:50:12 by apigeon           #+#    #+#             */
/*   Updated: 2022/12/16 11:06:22 by tperes           ###   ########.fr       */
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

/* TODO make an exit function that clear g_minishell
 */
t_list	*parse_line(char *line)
{
	t_list	*tokens;
	t_list	*commands;

	tokens = get_tokens(line);
	if (!tokens)
		return (NULL);
	if (lst_expand_var(tokens) == -1)
		return (ft_lstclear(&tokens, &free_token), NULL);
	if (lst_remove_quotes(tokens) == -1)
		return (ft_lstclear(&tokens, &free_token), NULL);
	if (!valid_syntax(tokens))
		return (ft_lstclear(&tokens, &free_token), NULL);
	commands = tokens_to_commands(tokens);
	ft_lstclear(&tokens, &free_token);
	return (commands);
}
