/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:59:39 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/03 11:49:40 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdbool.h>
# include "libft.h"

typedef enum e_token_type
{
	TOKEN_PIPE,
	TOKEN_RD_IN,
	TOKEN_RD_OUT,
	TOKEN_RD_APPEND,
	TOKEN_RD_HEREDOC,
	TOKEN_WORD,
}			t_token_type;

typedef enum e_redirect_type
{
	RD_IN,
	RD_OUT,
	RD_APPEND,
	RD_HEREDOC,
}			t_redirect_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}				t_token;

typedef struct s_redirect
{
	int				fd;
	char			*file;
	t_redirect_type	type;
}				t_redirect;

typedef struct s_command
{
	char	*cmd_full;
	char	*cmd;
	char	**args;
	t_list	*redirects;
}				t_command;

void	*parse_line(char *line);
t_list	*get_tokens(char *line);
void	free_token(void *ptr);

#endif
