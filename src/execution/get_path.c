/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:14:12 by tperes            #+#    #+#             */
/*   Updated: 2023/01/10 16:33:27 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

char	*get_path(char **path, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(tmp, "/");
		free(tmp);
		tmp = path[i];
		path[i] = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path[i], F_OK) == 0)
			return (path[i]);
		i++;
	}
	return (NULL);
}

char	*get_path_cmd(char *cmd)
{
	t_env	*env;
	t_list	*lst;
	char	**path;
	char	*tmp;

	env = NULL;
	lst = g_minishell.envs;
	while (lst != NULL)
	{
		env = lst->content;
		if (env == get_env_el("PATH"))
			break ;
		lst = lst->next;
	}
	path = ft_split(env->value, ':');
	tmp = get_path(path, cmd);
	if (tmp != NULL)
		return (tmp);
	return (NULL);
}