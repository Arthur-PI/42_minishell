/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 00:44:22 by apigeon           #+#    #+#             */
/*   Updated: 2022/12/10 00:44:23 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
