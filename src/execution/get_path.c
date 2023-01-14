/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tperes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:14:12 by tperes            #+#    #+#             */
/*   Updated: 2023/01/12 17:39:14 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_minishell	g_minishell;

char	*get_path(char **path, char *cmd)
{
	int		i;
	char	*tmp;
	char	*cmd_path;

	i = 0;
	cmd_path = NULL;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(tmp, "/");
		free(tmp);
		tmp = path[i];
		path[i] = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path[i], F_OK) == 0)
		{
			cmd_path = path[i];
			if (access(path[i], X_OK) == 0)
				return (path[i]);
		}
		i++;
	}
	return (cmd_path);
}

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

char	*get_path_cmd(char *cmd)
{
	t_env	*env;
	char	**path;
	char	*cmd_path;

	env = get_env_el("PATH");
	if (!env)
		return (NULL);
	path = ft_split(env->value, ':');
	if (!path)
		exit(12);
	cmd_path = get_path(path, cmd);
	if (cmd_path == NULL)
		return (NULL);
	cmd_path = ft_strdup(cmd_path);
	if (!cmd_path)
		exit(12);
	free_path(path);
	return (cmd_path);
}
