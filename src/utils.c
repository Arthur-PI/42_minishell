/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 22:48:56 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/26 22:48:59 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_concat(char *s1, char *s2)
{
	char	*new;

	if (!s1 || !s1[0])
	{
		if (s1)
			free(s1);
		return (s2);
	}
	else if (!s2 || !s2[0])
	{
		if (s2)
			free(s2);
		return (s1);
	}
	else
		new = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (new);
}

int	is_name_char(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (true);
	return (false);
}

int	is_quote(int c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

bool	is_empty(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
			return (false);
		i++;
	}
	return (true);
}

int	get_open_flag(t_redirect_type type)
{
	if (type == RD_IN)
		return (O_RDONLY);
	if (type == RD_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	if (type == RD_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	return (O_RDWR);
}
