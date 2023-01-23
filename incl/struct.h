/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:53:37 by apigeon           #+#    #+#             */
/*   Updated: 2023/01/21 12:54:21 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "libft.h"

typedef struct s_env
{
	char	*name;
	char	*value;
}				t_env;

typedef struct s_minishell
{
	int		signal;
	int		exit_status;
	void	*commands;
	t_list	*envs;
	char	*prompt;
}				t_minishell;

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
	RD_IN = 1,
	RD_OUT = 2,
	RD_APPEND = 4,
	RD_HEREDOC = 8,
}			t_redirect_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}				t_token;

typedef struct s_redirect
{
	int				fd;
	char			*file;
	t_redirect_type	type;
}				t_redirect;

typedef struct s_command
{
	int		pid;
	char	*cmd;
	char	**args;
	t_list	*redirects;
}				t_command;

#endif
