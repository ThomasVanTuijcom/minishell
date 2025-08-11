/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_command_roles.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:02:52 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/24 16:41:59 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	classify_cmd_token(t_p_node *node, int *cmd_found)
{
	if (node->prev && node->prev->token_type == CMD)
		*cmd_found = 1;
	if (node->token_type == EMPTY && *cmd_found)
		node->token_type = SIMPLE_ARG;
	if (!*cmd_found && node->token_type == EMPTY)
		node->token_type = CMD;
	if (node->prev && (node->prev->token_type == CMD
			|| node->prev->token_type == OPTION)
		&& node->content_exp_wq[0] == '-' && node->content_exp_wq[1] != '\0')
		node->token_type = OPTION;
	if (node->token_type == PIPE)
		*cmd_found = 0;
}

int	assign_command_roles(t_p_list *list)
{
	t_p_node	*node;
	int			cmd_found;

	if (!list || !list->head)
		return (0);
	cmd_found = 0;
	node = list->head;
	if (node->token_type == EMPTY)
		node->token_type = CMD;
	node = node->next;
	while (node)
	{
		classify_cmd_token(node, &cmd_found);
		node = node->next;
	}
	return (1);
}
