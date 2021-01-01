/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 23:35:53 by gihwan-kim        #+#    #+#             */
/*   Updated: 2021/01/01 14:23:57 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern t_list	*g_first_list;

/*
** ft_lstclear : before exit minishell clear cmd list data
*/

void			ft_exit(int exit_status)
{
	ft_lstclear(&(g_first_list->next), free_program);
	if (exit_status >= 256)
		exit(exit_status / 256);
	else
		exit(exit_status);
}
