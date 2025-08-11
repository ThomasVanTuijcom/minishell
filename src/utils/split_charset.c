/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_charset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:29:33 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/24 17:38:34 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char *str, char *charset)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			count_quoted_word(str, '\'', &count, &i);
		else if (str[i] == '"')
			count_quoted_word(str, '"', &count, &i);
		else if (is_charset(str[i], charset))
		{
			count++;
			while (str[i] && is_charset(str[i], charset))
				i++;
		}
		else if (!is_charset(str[i], charset))
		{
			count++;
			while (str[i] && !is_charset(str[i], charset))
				i++;
		}
	}
	return (count);
}

static char	**allocate_split_mem(char **addr, int wc)
{
	addr = malloc(sizeof(char *) * (wc + 1));
	if (!addr)
		return (NULL);
	addr[wc] = NULL;
	return (addr);
}

static int	word_length(char *str, char *charset)
{
	int	length;

	length = 0;
	if (*str && *str == '\'')
		length = length_word_quotes(str, '\'');
	else if (*str && *str == '"')
		length = length_word_quotes(str, '\"');
	else if (*str && is_charset(*str, charset))
	{
		while (*str && is_charset(*str, charset))
		{
			length++;
			str++;
		}
	}
	else if (*str && !is_charset(*str, charset))
	{
		while (*str && !is_charset(*str, charset))
		{
			length++;
			str++;
		}
	}
	return (length);
}

char	**ft_split_charset(char **splitted, char *str, char *charset)
{
	int	i;
	int	wl;
	int	wc;

	if (!str)
		return (NULL);
	i = 0;
	wl = 0;
	wc = count_words(str, charset);
	splitted = allocate_split_mem(splitted, wc);
	if (!splitted)
		return (NULL);
	while (i < wc)
	{
		wl = word_length(str, charset);
		splitted[i] = malloc(sizeof(char) * (wl + 1));
		if (!splitted[i])
			return (NULL);
		strlcpy_quotes(splitted[i], str, wl + 1);
		str += wl;
		i++;
	}
	return (splitted);
}
