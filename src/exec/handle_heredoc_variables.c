/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_variables.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:46:09 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/05 22:55:07 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_quotes(char *str)
{
	if (!str)
		return (-1);
	while (*str)
	{
		if (is_quote(*str))
			return (1);
		str++;
	}
	return (0);
}

int	get_total_length(char **lines)
{
	int	total_len;
	int	i;

	if (!lines)
		return (0);
	total_len = 0;
	i = 0;
	while (lines[i])
	{
		total_len += ft_strlen(lines[i]);
		i++;
	}
	return (total_len);
}

char	*join_lines(char **lines)
{
	char	*joined;
	int		total_len;
	int		i;
	int		j;
	int		k;

	if (!lines)
		return (NULL);
	total_len = get_total_length(lines);
	joined = malloc(total_len + 1);
	if (!joined)
		return (NULL);
	i = 0;
	j = 0;
	while (lines[i])
	{
		k = 0;
		while (lines[i][k])
			joined[j++] = lines[i][k++];
		i++;
	}
	joined[j] = '\0';
	return (joined);
}

static void	replace_char(char *str, char target, char replacement)
{
	while (*str)
	{
		if (*str == target)
			*str = replacement;
		str++;
	}
}

int	handle_heredoc_variables(char **hdoc, char *limitator, t_env_list *env)
{
	char	**lines;
	char	**expanded_lines;
	char	*joined;

	if (!hdoc || !*hdoc || !limitator)
		return (0);
	if (contains_quotes(limitator))
		return (-1);
	lines = ft_split(*hdoc, '\n');
	if (!lines)
		return (-1);
	expanded_lines = expand_heredoc_lines(lines, env);
	free_2d_array(lines);
	if (!expanded_lines)
		return (-1);
	joined = join_lines(expanded_lines);
	replace_char(joined, '\x01', '\n');
	free_2d_array(expanded_lines);
	if (!joined)
		return (-1);
	free(*hdoc);
	*hdoc = joined;
	return (0);
}
