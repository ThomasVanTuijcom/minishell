/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:31:10 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/14 12:32:40 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_metachar_type(int type)
{
	return (type == PIPE || type == REDIR_IN || type == REDIR_OUT
		|| type == APPEND || type == HEREDOC || type == WRONG_META);
}

int	is_invalid_followup_token(char *content)
{
	if (!content)
		return (0);
	if (!ft_strcmp(content, "<") || !ft_strcmp(content, "<<")
		|| !ft_strcmp(content, ">") || !ft_strcmp(content, ">>")
		|| !ft_strcmp(content, "|") || !ft_strcmp(content, "||")
		|| !ft_strcmp(content, "&") || !ft_strcmp(content, "&&")
		|| !ft_strcmp(content, ";"))
		return (1);
	return (0);
}

int	contains_metachar(char *content)
{
	if (!content)
		return (0);
	if (!ft_strcmp(content, "<") || !ft_strcmp(content, "<<")
		|| !ft_strcmp(content, ">") || !ft_strcmp(content, ">>")
		|| !ft_strcmp(content, "|") || !ft_strcmp(content, ";"))
		return (1);
	return (0);
}

int	only_metachars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_metachar(str[i]))
			return (0);
		i++;
	}
	return (1);
}
