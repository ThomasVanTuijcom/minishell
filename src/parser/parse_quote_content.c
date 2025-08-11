/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:15:46 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/24 17:36:41 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_single_quote_content(char **str, t_p_node *node)
{
	add_char_to_content_exp(str, node);
	while (**str != '\'')
		add_char_to_content_exp(str, node);
	add_char_to_content_exp(str, node);
}

void	parse_double_quote_content(char **str, t_p_node *node,
		t_env_list *env)
{
	char	current_char;
	char	next_char;
	int		can_expand_dollar;

	add_char_to_content_exp(str, node);
	while (**str != '\"' && **str != '\0')
	{
		current_char = **str;
		next_char = *(*str + 1);
		can_expand_dollar = (current_char == '$') && (next_char != '\"')
			&& (ft_isalnum(next_char) || next_char == '?');
		if (can_expand_dollar)
			add_string_to_content_exp(str, node, env);
		else
			add_char_to_content_exp(str, node);
	}
	add_char_to_content_exp(str, node);
}
