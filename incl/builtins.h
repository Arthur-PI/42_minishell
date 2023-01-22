/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apigeon <apigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:51:12 by apigeon           #+#    #+#             */
/*   Updated: 2022/12/09 13:24:47 by tperes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/param.h>

# include "libft.h"
# include "struct.h"

int		pwd(int ac);
int		echo(int ac, char **av);
int		my_exit(int ac, char **av);
int		cd(int ac, char **av);
int		my_env(int ac, char **av);
int		my_unset(int ac, char **av);
int		my_export(int ac, char **av);
void	free_env(void *ptr);
t_list	*add_env(t_list *lst, char *env);
t_env	*get_env_el(char *s);
t_list	*tab_to_list(char **env);
t_env	*create_env(char *env);
t_list	*add_empty_env(t_list *lst, char *s);

#endif
