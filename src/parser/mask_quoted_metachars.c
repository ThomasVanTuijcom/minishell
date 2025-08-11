/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask_quoted_metachars.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:06:04 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/24 16:56:56 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quoted_string(const char *str, int *i, int *j, t_p_node *node)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
	{
		if (is_metachar(str[*i]))
			node->q_meta_indexes[(*j)++] = *i;
		(*i)++;
	}
	if (str[*i] == quote)
		(*i)++;
}

int	fill_index_meta(char *str, t_p_node *node)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			skip_quoted_string(str, &i, &j, node);
		else
			i++;
	}
	return (0);
}

int	count_metachars_inside_double_quotes(char *str)
{
	int		i;
	bool	inside_quotes;
	int		count;

	i = 0;
	inside_quotes = false;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			inside_quotes = !inside_quotes;
		else if (inside_quotes && is_metachar(str[i]))
			count++;
		i++;
	}
	return (count);
}

void	mask_content(char *str, int amount, t_p_node *node)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		if (str[node->q_meta_indexes[i]] == '|')
			str[node->q_meta_indexes[i]] = '0';
		else if (str[node->q_meta_indexes[i]] == '&')
			str[node->q_meta_indexes[i]] = '1';
		else if (str[node->q_meta_indexes[i]] == ';')
			str[node->q_meta_indexes[i]] = '2';
		else if (str[node->q_meta_indexes[i]] == '<')
			str[node->q_meta_indexes[i]] = '3';
		else if (str[node->q_meta_indexes[i]] == '>')
			str[node->q_meta_indexes[i]] = '4';
		i++;
	}
}

int	mask_quoted_metachars(char *content, t_p_node *node)
{
	int	amount_metachars;

	amount_metachars = count_metachars_inside_double_quotes(content);
	if (amount_metachars == 0)
		return (0);
	node->q_meta_indexes = ft_calloc(amount_metachars, sizeof(int));
	fill_index_meta(content, node);
	mask_content(content, amount_metachars, node);
	return (amount_metachars);
}
