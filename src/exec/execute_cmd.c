/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:23:53 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/07 18:15:42 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	reset_io(int exec_data[5], t_p_list *list, int n)
{
	if (n == 1)
	{
		dup2(exec_data[EXEC_STDIN_COPY], STDIN_FILENO);
		dup2(exec_data[EXEC_STDOUT_COPY], STDOUT_FILENO);
	}
	else if (n == 2)
	{
		if (exec_data[EXEC_INDEX] > 1)
			close(exec_data[EXEC_PIPE_FD]);
		if (exec_data[EXEC_TOTAL_CMDS] > 1)
		{
			exec_data[EXEC_PIPE_FD] = list->pipe[0];
			close(list->pipe[1]);
		}
	}
	return (0);
}

void	cleanup_redundant_outfiles(t_p_list *list)
{
	t_p_node	*curr;
	bool		is_last_redirection;
	int			fd;

	curr = list->tail;
	is_last_redirection = true;
	while (curr)
	{
		fd = -1;
		if (curr->token_type == PIPE)
			is_last_redirection = true;
		if ((curr->token_type == OUTFILE || curr->token_type == APPEND_OF))
		{
			if (!is_last_redirection)
			{
				unlink(curr->content);
				fd = open(curr->content, O_WRONLY | O_CREAT | O_TRUNC, 0664);
				close(fd);
			}
			else
				is_last_redirection = false;
		}
		curr = curr->prev;
	}
}

int	execute_cmd(t_data *data, t_p_list *list)
{
	int			exec_data[5];
	t_p_node	*curr;

	curr = list->head;
	exec_data[EXEC_INDEX] = 0;
	exec_data[EXEC_TOTAL_CMDS] = count_cmd_nodes(list);
	exec_data[EXEC_PIPE_FD] = 0;
	exec_data[EXEC_STDIN_COPY] = dup(STDIN_FILENO);
	exec_data[EXEC_STDOUT_COPY] = dup(STDOUT_FILENO);
	modify_signal_handlers();
	cleanup_redundant_outfiles(data->parser);
	while (curr)
	{
		if (curr->token_type == CMD || !curr->index)
		{
			exec_data[EXEC_INDEX]++;
			execute_node(exec_data, curr, data);
			close_exec(curr, list, exec_data);
		}
		curr = curr->next;
	}
	close_exec_p(list, exec_data);
	return (0);
}
