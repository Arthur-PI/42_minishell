/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_rd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 21:48:59 by apigeon           #+#    #+#             */
/*   Updated: 2023/01/05 21:49:01 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_redirect_type	get_redirection_type(t_token_type type)
{
	if (type == TOKEN_RD_IN)
		return (RD_IN);
	else if (type == TOKEN_RD_OUT)
		return (RD_OUT);
	else if (type == TOKEN_RD_APPEND)
		return (RD_APPEND);
	else
		return (RD_HEREDOC);
}

static int	get_open_flag(t_redirect_type type)
{
	if (type == RD_IN)
		return (O_RDONLY);
	if (type == RD_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	if (type == RD_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (O_RDWR);
}

static int	open_fd(t_redirect_type type, t_token *name)
{
	int		fd;
	char	*s;

	s = name->value;
	if (type == RD_HEREDOC)
		fd = handle_heredoc(s);
	else
	{
		fd = open(s, get_open_flag(type), 0644);
		if (fd == -1)
			printf(FILE_ERROR_MSG, s);
	}
	return (fd);
}

static bool	add_redirect(t_command *cmd, t_list *rd_type, t_list *file)
{
	int				fd;
	t_redirect		*rd;
	t_redirect_type	type;

	if (!file)
		return (NULL);
	type = get_redirection_type(((t_token *) rd_type->content)->type);
	fd = open_fd(type, file->content);
	if (fd == -1)
		return (false);
	rd = malloc(sizeof(*rd));
	rd->file = ft_strdup(((t_token *)file->content)->value);
	rd->type = type;
	rd->fd = fd;
	ft_lstadd_back(&cmd->redirects, ft_lstnew(rd));
	return (true);
}

int	process_rd(t_token *token, t_command **command, t_list **tokens)
{
	if (token->type != TOKEN_WORD && token->type != TOKEN_PIPE)
	{
		if (*command == NULL)
			*command = create_command(NULL);
		if (!add_redirect(*command, *tokens, (*tokens)->next))
			return (-1);
		*tokens = (*tokens)->next;
	}
	return (1);
}
