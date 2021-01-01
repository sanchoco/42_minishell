/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:07:34 by sancho            #+#    #+#             */
/*   Updated: 2020/12/31 20:31:53 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_env(char *str, char *envv)
{
	int		i;

	i = 0;
	while (str[i] && envv[i] && (str[i] == envv[i]) && (str[i] != '=')
		&& (envv[i] != '='))
		i++;
	if (i == 0)
		return (0);
	if (((envv[i] == '=') && (str[i] == '=')) ||
		((envv[i] == '=') || str[i] == 0))
		return (1);
	return (0);
}

/*
** if program is only export string
** print envp
** Ex.
** export				: O -> print_export
** export name=value	: X -> ft_export
*/

int	print_export(char **envv)
{
	int	i;

	i = -1;
	while (envv[++i])
	{
		ft_putstr_fd(envv[i], 1);
		write(1, "\n", 1);
	}
	return (SUCCESS);
}

void
	ft_export_new(char *str, char **new, int i)
{
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
}

int	ft_export(char *str, char ***envv)
{
	int		i;
	char	**new;

	if (str[0] == '=' || str[0] == '\0')
		return (ERROR);
	i = -1;
	while ((*envv)[++i] != NULL)
		if (check_env(str, (*envv)[i]))
		{
			free((*envv)[i]);
			(*envv)[i] = ft_strdup(str);
			return (SUCCESS);
		}
	if (!(new = malloc(sizeof(char*) * (i + 2))))
		return (ERROR);
	i = -1;
	while ((*envv)[++i])
	{
		new[i] = ft_strdup((*envv)[i]);
		free((*envv)[i]);
	}
	ft_export_new(str, new, i);
	free(*envv);
	*envv = new;
	return (SUCCESS);
}
