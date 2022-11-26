/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:40:58 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/26 22:53:48 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* remove quotes (single or double) that surround a WORD.
 * e.g: abc" J'arrive "def' ici".'  -> abc J'arrive def ici".
 * e.g: "Bonjour j'arrive."  -> Bonjour j'arrive
 */
void	remove_quotes(char *s)
{
	int		i;
	int		nb_quotes;
	char	current_quote;

	i = 0;
	nb_quotes = 0;
	current_quote = 0;
	while (s[i])
	{
		if (is_quote(s[i]) && current_quote == 0)
		{
			nb_quotes++;
			current_quote = s[i];
		}
		else if (s[i] == current_quote)
		{
			nb_quotes++;
			current_quote = 0;
		}
		else
			s[i - nb_quotes] = s[i];
		i++;
	}
	s[i - nb_quotes] = s[i];
}

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

// return a copy of s with all environment variables replace by there values.
// e.g. s = "Hello i am $NAME, and i'm $AGE. Thank you"
// -> "Hello i am Arthur, and i'm 21. Thank you"
char	*replace_envs(char *s)
{
	int		i;
	int		start;
	char	*env;
	char	*env_value;
	char	*new;

	i = 0;
	start = 0;
	env = NULL;
	new = NULL;
	while (s[i])
	{
		if (s[i] == '$')
		{
			new = ft_concat(new, ft_substr(s, start, i - start));
			env = extract_env_name(s, i);
			env_value = get_env_value(env);
			new = ft_concat(new, env_value);
			if (env)
				i += ft_strlen(env);
			free(env);
			start = i + 1;
		}
		i++;
	}
	new = ft_concat(new, ft_substr(s, start, i - start));
	return (new);
}
