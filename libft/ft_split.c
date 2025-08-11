/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:35:16 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/29 11:29:35 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(const char *str, int n)
{
	char	*result;
	int		i;

	if (!str)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (n + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static int	count_words(const char *str, char c)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i])
	{
		if (str[i] != c && !in_word)
		{
			count++;
			in_word = 1;
		}
		else if (str[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

static void	free_2d_array_n(char **array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static int	add_to_array(char ***array, int curr_index, const char *s, int n)
{
	(*array)[curr_index] = ft_strndup(s, n);
	if (!(*array)[curr_index])
	{
		free_2d_array_n(*array, curr_index);
		return (-1);
	}
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	int		i;
	int		curr_index;
	int		start;

	i = 0;
	result = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!result || !s)
		return (NULL);
	curr_index = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			if (add_to_array(&result, curr_index++, &s[start], i - start) < 0)
				return (NULL);
		}
		else
			i++;
	}
	result[curr_index] = NULL;
	return (result);
}
