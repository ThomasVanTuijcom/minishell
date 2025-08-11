/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:16:59 by tvan-tui          #+#    #+#             */
/*   Updated: 2024/10/17 12:27:02 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	count_length(char const *str, char const *set)
{
	int	count;
	int	i;
	int	str_length;

	i = 0;
	count = 0;
	str_length = ft_strlen(str);
	while (str[i] && char_in_set(str[i], set))
	{
		count++;
		i++;
	}
	if (str[i])
	{
		i = ft_strlen(str) - 1;
		while (str[i] && char_in_set(str[i], set))
		{
			count++;
			i--;
		}
	}
	return (str_length - count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (s1[i] && char_in_set(s1[i], set))
		i++;
	trimmed = ft_substr(s1, i, count_length(s1, set));
	if (!trimmed)
		return (NULL);
	return (trimmed);
}
