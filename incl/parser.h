/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:59:39 by apigeon           #+#    #+#             */
/*   Updated: 2022/10/31 14:59:25 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include "libft.h"

enum e_token_type
{
	PIPE,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_HEREDOC,
	REDIRECT_APPEND,
	WORD,
};

typedef struct s_token
{
	int		type;
	char	*value;
}				t_token;

void*	parse_line(char *line);
t_list*	get_tokens(char *line);

#endif
