/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:34:39 by gihwan-kim        #+#    #+#             */
/*   Updated: 2021/01/01 14:32:02 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_status = 0;
int		g_signal = 1;
char	**g_envp = NULL;

void	prompt(void)
{
	ft_putstr_fd("minishell-", STDERR_FILENO);
	ft_putstr_fd(VERSION, STDERR_FILENO);
	ft_putstr_fd("$ ", STDERR_FILENO);
}

void	handler(int signo)
{
	(void)signo;
	g_exit_status = 256;
	write(STDERR_FILENO, "\b\b", 2);
	if (signo != SIGTERM)
		write(STDERR_FILENO, "  \n", 3);
	if (g_signal)
		prompt();
}

int		check_line_is_only_white_space(char *line)
{
	int		i;
	int		line_len;

	i = 0;
	line_len = (int)ft_strlen(line);
	if (!line_len)
		return (TRUE);
	while (*line)
	{
		if (*line == '\t' || *line == '\r' || *line == '\v' || *line == '\f')
			return (TRUE);
		if (*line == ' ')
			i++;
		line++;
	}
	if (i == line_len)
		return (TRUE);
	return (FALSE);
}

int		minishell(void)
{
	t_list	*cmd_list;
	char	*line;

	line = NULL;
	while (1)
	{
		prompt();
		if (!get_next_line(0, &line) && !ft_strlen(line))
		{
			g_signal = 0;
			free(line);
			exit(BASH_SUCCESS);
		}
		else if (!check_line_is_only_white_space(line) &&
				(cmd_list = parsing_first(line)))
		{
			g_signal = 0;
			controller(cmd_list);
		}
		free(line);
		g_signal = 1;
	}
}

int		main(int argc, char **argv, char **envv)
{
	(void)argc;
	(void)argv;
	g_envp = ft_first_envv(envv);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	signal(SIGTERM, handler);
	minishell();
	return (g_exit_status);
}
