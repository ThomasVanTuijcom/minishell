/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:55:16 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/12 18:22:45 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data_fd(t_data *data)
{
	t_p_node	*node;

	if (!data || !data->parser)
		return ;
	if (data->parser->pipe[0] >= 0)
		close(data->parser->pipe[0]);
	if (data->parser->pipe[1] >= 0)
		close(data->parser->pipe[1]);
	node = data->parser->head;
	while (node)
	{
		if (node->fd[0] >= 0)
			close(node->fd[0]);
		if (node->fd[1] >= 0)
			close(node->fd[1]);
		node = node->next;
	}
}
