/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parser_content.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:17:15 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/07 15:08:08 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_expanded_string_quotes(t_p_node *node)
{
	int	i;
	int	j;
	int	length;
	int	quote_type;

	i = 0;
	j = 0;
	length = get_word_length(node->content_exp);
	node->content_exp_wq = ft_calloc((length + 1), sizeof(char));
	if (!node->content_exp_wq)
		return ;
	while (node->content_exp[i])
	{
		quote_type = is_quote(node->content_exp[i]);
		if (quote_type == 1)
			put_content_exp_wq(node, &i, &j, '\'');
		else if (quote_type == 2)
			put_content_exp_wq(node, &i, &j, '\"');
		else
			node->content_exp_wq[j++] = node->content_exp[i++];
	}
}

char	*restore_q_from_markers(char *content)
{
	int		i;
	char	*result;

	if (!content)
		return (NULL);
	result = ft_calloc(ft_strlen(content) + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (content[i])
	{
		if (content[i] == 6)
			result[i] = '\'';
		else if (content[i] == 8)
			result[i] = '\"';
		else
			result[i] = content[i];
		i++;
	}
	free(content);
	return (result);
}

void	expand_parser_content(char *str, t_p_node *tail, t_env_list *env)
{
	if (!str)
		return ;
	parse_and_expand_dollars(&str, tail, env);
	process_expanded_string_quotes(tail);
	if (tail->has_quote)
	{
		tail->content_exp = restore_q_from_markers(tail->content_exp);
		tail->content_exp_wq = restore_q_from_markers(tail->content_exp_wq);
	}
	return ;
}
