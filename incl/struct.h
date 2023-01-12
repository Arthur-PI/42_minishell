/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 17:53:37 by apigeon           #+#    #+#             */
/*   Updated: 2023/01/10 13:51:02 by tperes           ###   ########.fr       */
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
	t_list	*envs;
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
	char	*cmd;
	char	**args;
	t_list	*redirects;
	int	pid;
}				t_command;

#endif
