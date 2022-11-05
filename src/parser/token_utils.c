/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:04:17 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/05 12:04:47 by apigeon          ###   ########.fr       */
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

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}
