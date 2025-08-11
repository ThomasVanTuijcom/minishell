/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:57:31 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/29 13:12:47 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_interior_spaces(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		while (str[i] && !is_space(str[i]))
		{
			i++;
			len++;
		}
		if (str[i] && is_space(str[i]))
		{
			i++;
			len++;
		}
		while (str[i] && is_space(str[i]))
			i++;
	}
	return (len);
}

char	*trim_interior_spaces(char *str)
{
	char	*nstr;
	int		len;
	int		i;
	int		j;

	nstr = NULL;
	i = 0;
	j = 0;
	len = len_interior_spaces(str);
	nstr = (char *)malloc(sizeof(char) * (len + 1));
	while (str[i])
	{
		while (str[i] && !is_space(str[i]))
			nstr[j++] = str[i++];
		if (str[i] && is_space(str[i]))
			nstr[j++] = str[i++];
		while (str[i] && is_space(str[i]))
			i++;
	}
	nstr[j] = '\0';
	free(str);
	return (nstr);
}
