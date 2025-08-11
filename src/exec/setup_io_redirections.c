/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_io_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:42:00 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/11 17:41:44 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_hdocs(char **hdocs)
{
	int	count;

	if (!hdocs)
		return (0);
	count = 0;
	while (hdocs[count])
		count++;
	return (count);
}

void	setup_io_redirections(t_data *data, t_p_node *node, char **fds)
{
	bool		input;
	bool		output;
	t_p_node	*curr;

	if (!fds)
		return ;
	input = false;
	output = false;
	curr = get_first_node_in_pipeline(node);
	while (curr && curr->token_type != PIPE)
	{
		handle_input_redirection(data, node, curr, &input);
		handle_output_redirection(node, curr, &output);
		curr = curr->next;
	}
}
