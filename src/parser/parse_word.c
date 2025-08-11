/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:54:57 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/07 15:02:59 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len_word_in_quotes(char quote, char *line, int *pos, int length)
{
	(*pos)++;
	length++;
	while (line[*pos] && line[*pos] != quote)
	{
		(*pos)++;
		length++;
	}
	(*pos)++;
	length++;
	return (length);
}

int	check_length_of_word(char *word)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	while (word[i] && !is_space(word[i]))
	{
		if (word[i] == '\'')
			length = get_len_word_in_quotes('\'', word, &i, length);
		else if (word[i] == '\"')
			length = get_len_word_in_quotes('\"', word, &i, length);
		else
		{
			i++;
			length++;
		}
	}
	return (length);
}

int	parse_word(char **line, t_p_list **parser)
{
	int			i;
	char		*word;
	t_p_node	*node;

	if (!*line || **line == '\0')
		return (0);
	i = check_length_of_word(*line);
	word = ft_substr(*line, 0, i);
	if (!word)
		return (0);
	node = new_p_node(word);
	if (!node)
	{
		free(word);
		return (0);
	}
	p_list_addback(parser, node);
	*line = *line + i;
	free(word);
	return (i);
}
