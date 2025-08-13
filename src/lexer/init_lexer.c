/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:42:08 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/13 21:29:00 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	pipe_followed_by_redir(t_p_node *curr)
{
	return (curr->token_type == PIPE && (curr->next->token_type == REDIR_IN
			|| curr->next->token_type == REDIR_OUT
			|| curr->next->token_type == APPEND
			|| curr->next->token_type == HEREDOC));
}

int	has_invalid_meta_sequence(t_p_list *list)
{
	t_p_node	*curr;

	curr = list->head;
	while (curr && curr->next)
	{
		if (!pipe_followed_by_redir(curr) && (contains_metachar(curr->content)
				&& is_invalid_followup_token(curr->next->content)))
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	init_lexer(t_data *data)
{
	if (!data->parser)
		return (0);
	assign_argument_types(data->parser);
	assign_command_roles(data->parser);
	if (syntax_error_meta(data->parser) < 0
		|| has_invalid_meta_sequence(data->parser))
		return (0);
	return (1);
}
