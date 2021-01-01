/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 16:58:00 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/21 16:58:51 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
#define BUILTIN_H

#include "minishell.h"

char	**ft_first_envv(char **envv);

int	    check_env(char *str, char *envv);
int		ft_echo(char **program);
int		ft_env(char **envv);
int		ft_execve(char **info, char **envv);
int		ft_export(char *str, char ***envv);
int		ft_unset(char *str, char ***envv);
int		ft_cd(char *src, char **envv);
int		ft_pwd(void);
void	ft_exit(int exit_status);
int		check_unset(char *str, char *envv);
int 	print_export(char **envv);

#endif
