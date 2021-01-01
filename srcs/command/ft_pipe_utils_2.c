/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gihwan-kim <kgh06079@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 21:58:09 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/17 21:58:21 by gihwan-kim       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

void	close_pipe(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	free_pipe_sub_shell_arr(int **pipe_fd, pid_t *sub_shell_arr)
{
	int	idx;

	idx = -1;
	while (pipe_fd[++idx])
		free(pipe_fd[idx]);
	free(pipe_fd);
	free(sub_shell_arr);
}
