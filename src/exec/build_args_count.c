/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_args_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:24:33 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/16 16:24:43 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd_args(t_p_node *node)
{
	int			count;
	t_p_node	*curr;

	count = 1;
	curr = node->next;
	while (curr && curr->token_type != PIPE)
	{
		if (curr->token_type == OPTION || curr->token_type == SIMPLE_ARG)
			count++;
		curr = curr->next;
	}
	return (count);
}

int	*build_cmd_args_counts(t_p_list *list, int size)
{
	int			*counts;
	int			index;
	t_p_node	*node;

	counts = malloc(sizeof(int) * size);
	index = 0;
	node = list->head;
	if (!counts)
		return (NULL);
	while (node)
	{
		if (node->token_type == CMD)
			counts[index++] = count_cmd_args(node);
		node = node->next;
	}
	return (counts);
}
