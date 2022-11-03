/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:51:12 by apigeon           #+#    #+#             */
/*   Updated: 2022/11/02 15:09:50 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/param.h>
# include "libft.h"

typedef struct s_env{
	char	**tab;
	char	*name;
	char	*value;
	t_list	*list;
}				t_env;

int	pwd(int ac);
int	echo(int ac, char **av);
int	my_exit(int ac, char **av);
int cd(int ac, char **av);
int	my_env(int ac, char **av, char **env);

#endif
