/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:50:28 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/07 15:00:18 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_unquoted_meta(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_quote(str[i]) == 1)
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		else if (is_quote(str[i]) == 2)
		{
			i++;
			while (str[i] != '"')
				i++;
		}
		else if (is_metachar(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	get_word_length(char *word)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	while (word[i])
	{
		if (word[i] == '\'')
			length = get_len_in_quotes('\'', word, &i, length);
		else if (word[i] == '\"')
			length = get_len_in_quotes('\"', word, &i, length);
		else
		{
			i++;
			length++;
		}
	}
	return (length);
}

int	skip_spaces(char **line)
{
	int	i;

	i = 0;
	while (**line && is_space(**line))
	{
		(*line)++;
		i++;
	}
	return (i);
}

char	*copy_word_without_quotes(char **src, char *dest)
{
	int		i;
	char	quote;

	i = 0;
	while (**src && !is_space(**src))
	{
		if (**src == '\"' || **src == '\'')
		{
			quote = *(*src)++;
			while (**src && **src != quote)
				dest[i++] = *(*src)++;
			if (**src == quote)
				(*src)++;
		}
		else
			dest[i++] = *(*src)++;
	}
	dest[i] = '\0';
	return (dest);
}

int	get_len_in_quotes(char quote, char *line, int *pos, int length)
{
	(*pos)++;
	while (line[*pos] && line[*pos] != quote)
	{
		(*pos)++;
		length++;
	}
	(*pos)++;
	return (length);
}
