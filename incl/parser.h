/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:59:39 by apigeon           #+#    #+#             */
/*   Updated: 2023/01/18 17:13:52 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/stat.h>

# include "struct.h"
# include "libft.h"
# include "utils.h"
# include "builtins.h"

# define ERROR_MALLOC 1
# define NO_ERROR 0

# define FILE_ERROR_MSG "minishell: %s: No such file or directory\n"

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
bool			is_directory(const char *path);

#endif
