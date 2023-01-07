/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:59:39 by apigeon           #+#    #+#             */
/*   Updated: 2022/12/16 18:38:15 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdbool.h>
# include "minishell.h"
# include "libft.h"
# include "utils.h"
# include "builtins.h"

# define ERROR_MALLOC 1
# define NO_ERROR 0

# define FILE_ERROR_MSG "Error: '%s' not such file or permission denied\n"

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
}				t_command;

int				is_operator(char c);
void			free_token(void *ptr);
t_list			*parse_line(char *line);
t_list			*get_tokens(char *line);
t_token_type	get_token_type(char *token_value);
void			remove_quotes(char *s);
char			*replace_envs(char *s);
void			print_tokens(t_list *tokens);
t_token			*new_token(char *value, t_token_type type);
int				lst_remove_quotes(t_list *lst);
int				lst_expand_var(t_list *lst);
void			print_commands(t_list *commands);
int				valid_syntax(t_list *tokens);
void			free_command(void *ptr);
t_list			*tokens_to_commands(t_list *tokens);
int				handle_heredoc(char *stop);
t_command		*create_command(t_token *token);
int				process_rd(t_token *t, t_command **c, t_list **ts);

#endif
