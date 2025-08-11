/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:20:49 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/05 22:53:02 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_heredoc_line(char **line, char ***result)
{
	char	*tmp;

	tmp = NULL;
	if (*(*line))
	{
		tmp = *line;
		*line = ft_strjoin(*line, "\n");
		if (!*line)
			return (0);
		free(tmp);
		tmp = NULL;
		tmp = ft_strjoin(*(*result), *line);
	}
	else
		tmp = ft_strjoin(*(*result), "\x01");
	return (tmp);
}

int	collect_heredoc_lines(char **result, const char *delimitor_nl)
{
	char	*line;
	char	*tmp;

	tmp = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (0);
		tmp = process_heredoc_line(&line, &result);
		if (!ft_strcmp(line, delimitor_nl))
		{
			free(line);
			free(tmp);
			break ;
		}
		free(line);
		if (!tmp)
			return (0);
		free(*result);
		*result = tmp;
	}
	return (1);
}

int	read_heredoc(char **heredoc, char *delimitor)
{
	char	*result;
	char	*delimitor_nl;

	result = ft_strdup("");
	if (!result)
		return (0);
	delimitor_nl = ft_strjoin(delimitor, "\n");
	if (!delimitor_nl)
		return (free(result), 0);
	if (!collect_heredoc_lines(&result, delimitor_nl))
	{
		free(result);
		free(delimitor_nl);
		return (0);
	}
	free(delimitor_nl);
	*heredoc = result;
	return (1);
}
