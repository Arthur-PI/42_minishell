/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 22:54:42 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/26 22:54:44 by apigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>
# include <sys/types.h>
# include <fcntl.h>

# include "libft.h"
# include "struct.h"

char	*ft_concat(char *s1, char *s2);
int		is_name_char(int c);
int		is_quote(int c);

#endif
