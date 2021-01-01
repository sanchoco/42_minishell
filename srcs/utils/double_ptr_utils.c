/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_ptr_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sancho <sancho@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 23:04:49 by gihwan-kim        #+#    #+#             */
/*   Updated: 2020/12/31 21:10:34 by sancho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_splitjoin(char **split1, char **split2)
{
	char	**ret;
	int		i1;
	int		i2;

	i1 = 0;
	if (split1)
		while (split1[i1])
			i1++;
	i2 = 0;
	while (split2[i2])
		i2++;
	if (!(ret = ft_calloc(i2 + i1 + 1, sizeof(char*))))
		return (ret);
	i1 = -1;
	if (split1)
		while (split1[++i1])
			ret[i1] = ft_strdup(split1[i1]);
	else
		i1 = 0;
	i2 = -1;
	while (split2[++i2])
		ret[i1 + i2] = ft_strdup(split2[i2]);
	return (ret);
}

void	free_double_str(char **ptr)
{
	int idx;

	idx = 0;
	if (ptr)
	{
		while (ptr[idx])
		{
			free(ptr[idx]);
			ptr[idx] = NULL;
			idx++;
		}
		free(ptr);
		ptr = NULL;
	}
}

int		double_str_len(char **str)
{
	int idx;

	idx = 0;
	while (str[idx])
		idx++;
	return (idx);
}

/*
** add str to ptr and make new ptr
** free previous ptr
*/

char	**add_double_str(char **ptr, char *str)
{
	char	**ret;
	int		len;
	int		idx;

	len = double_str_len(ptr) + 2;
	if (!(ret = ft_calloc(len, sizeof(char*))))
		return (NULL);
	idx = 0;
	while (ptr[idx])
	{
		ret[idx] = ft_strdup(ptr[idx]);
		idx++;
	}
	ret[idx] = ft_strdup(str);
	free_double_str(ptr);
	return (ret);
}
