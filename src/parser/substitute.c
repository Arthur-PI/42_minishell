/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:40:58 by apigeon           #+#    #+#             */
/*   Updated: 2022/12/10 21:34:44 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

extern t_minishell	g_minishell;

/* extract the env variable such as $NAME in a string
 * given the start of the $ sign.
 * e.g. s = "Bonjour $NAME" and i = 8 -> "$NAME"
 */
static char	*extract_env_name(char *s, size_t start)
{
	size_t	end;
	char	*env_name;

	start++;
	end = start;
	if (s[start] && !ft_isdigit(s[end++]))
	{
		while (is_name_char(s[end]))
			end++;
	}
	env_name = ft_substr(s, start, end - start);
	return (env_name);
}

static t_env	*get_env(char *s)
{
	t_env	*env;
	t_list	*envs;

	envs = g_minishell.envs;
	while (envs)
	{
		env = envs->content;
		if (ft_strcmp(s, env->name) == 0)
			return (env);
		envs = envs->next;
	}
	return (NULL);
}

// given an environment variable name, give its value.
// e.g. env = "$NAME" -> "Arthur"
static char	*get_env_value(char *name)
{
	t_env	*env;
	char	*env_value;

	env_value = NULL;
	env = get_env(name);
	if (env)
		env_value = ft_strdup(env->value);
	return (env_value);
}

static char	*replace_env(char *s, char *old, uint *end, uint *start)
{
	char	*env;
	char	*tmp;
	char	*env_value;

	tmp = ft_substr(s, *start, (*end) - (*start));
	if (!tmp)
		return (NULL);
	old = ft_concat(old, tmp);
	if (!old)
		return (free(tmp), NULL);
	env = extract_env_name(s, *end);
	if (!env)
		return (free(tmp), free(old), NULL);
	env_value = get_env_value(env);
	if (!env_value)
		return (free(tmp), free(old), free(env_value), NULL);
	old = ft_concat(old, env_value);
	if (!old)
		return (free(tmp), free(env_value), NULL);
	*end += ft_strlen(env);
	free(env);
	*start = (*end) + 1;
	return (old);
}

// return a copy of s with all environment variables replace by there values.
// e.g. s = "Hello i am $NAME, and i'm $AGE. Thank you"
// -> "Hello i am Arthur, and i'm 21. Thank you"
char	*replace_envs(char *s)
{
	uint	i;
	uint	start;
	char	quote;
	char	*new;

	i = -1;
	start = 0;
	new = NULL;
	quote = 0;
	while (s[++i])
	{
		if (is_quote(s[i]) && quote == 0)
			quote = s[i];
		else if (is_quote(s[i]) && s[i] == quote)
			quote = 0;
		if (quote != '\'' && s[i] == '$')
		{
			new = replace_env(s, new, &i, &start);
			if (!new)
				return (s);
		}
	}
	new = ft_concat(new, ft_substr(s, start, i - start));
	free(s);
	return (new);
}
