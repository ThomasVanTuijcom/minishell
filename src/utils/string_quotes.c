/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 17:34:57 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/10 16:08:50 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cpy_quotes(size_t *i, size_t *j, char *dest, char *src)
{
	if (src[*i] && src[*i] == '\"')
	{
		dest[(*j)++] = src[(*i)++];
		while (src[*i] && src[*i] != '\"')
		{
			dest[(*j)++] = src[(*i)++];
		}
		dest[(*j)++] = src[(*i)++];
	}
	else if (src[*i] && src[*i] == '\'')
	{
		dest[(*j)++] = src[(*i)++];
		while (src[*i] && src[*i] != '\'')
		{
			dest[(*j)++] = src[(*i)++];
		}
		dest[(*j)++] = src[(*i)++];
	}
	else
		dest[(*j)++] = src[(*i)++];
}

size_t	strlcpy_quotes(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!src)
		return (0);
	if (size > 0)
	{
		while (src[i] && i < size - 1)
			cpy_quotes(&i, &j, dest, src);
		dest[j] = 0;
	}
	return (ft_strlen(src));
}

char	*add_char_to_string(char *s1, char c)
{
	int		length;
	char	*str;

	if (c != 0)
	{
		length = ft_strlen(s1);
		str = malloc(sizeof(char) * (length + 2));
		if (!str)
			return (NULL);
		ft_memcpy(str, s1, length);
		str[length] = c;
		str[length + 1] = '\0';
		free(s1);
		return (str);
	}
	return (s1);
}
