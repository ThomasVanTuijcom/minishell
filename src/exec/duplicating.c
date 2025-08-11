/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicating.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:05:45 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/07 20:42:23 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_return(int datas[5], t_p_list *list)
{
	close_all(datas, list);
	return (-1);
}

int	close_all(int exec_data[5], t_p_list *list)
{
	t_p_node	*curr;

	if (exec_data[EXEC_PIPE_FD] > 0)
		close(exec_data[EXEC_PIPE_FD]);
	if (exec_data[EXEC_INDEX] < exec_data[EXEC_TOTAL_CMDS])
		close(list->pipe[1]);
	else
		close(list->pipe[0]);
	curr = list->head;
	while (curr)
	{
		if (curr->fd[0] > 0)
			close(curr->fd[0]);
		if (curr->fd[1] > 0)
			close(curr->fd[1]);
		curr = curr->next;
	}
	return (0);
}

int	setup_last_command(int exec_data[5], t_p_list *list, t_p_node *node)
{
	if (node->fd[0] > 0 && dup2(node->fd[0], STDIN_FILENO) < 0)
		return (close_return(exec_data, list));
	else if (node->fd[0] < 1 && dup2(exec_data[EXEC_PIPE_FD], STDIN_FILENO) < 0)
		return (close_return(exec_data, list));
	if (node->fd[1] > 0 && dup2(node->fd[1], STDOUT_FILENO) < 0)
		return (close_return(exec_data, list));
	if (exec_data[EXEC_PIPE_FD] > 0)
		close(exec_data[EXEC_PIPE_FD]);
	if (node->fd[1] > 0)
		close(node->fd[1]);
	close(list->pipe[0]);
	close(list->pipe[1]);
	close(exec_data[EXEC_STDIN_COPY]);
	close(exec_data[EXEC_STDOUT_COPY]);
	return (0);
}

int	duplicating(int exec_data[5], t_p_list *list, t_p_node *node)
{
	int	curr_cmd;
	int	total_cmd;

	curr_cmd = exec_data[EXEC_INDEX];
	total_cmd = exec_data[EXEC_TOTAL_CMDS];
	if (curr_cmd == 1)
		return (setup_first_command(exec_data, list, node));
	else if (curr_cmd == total_cmd && total_cmd > 1)
		return (setup_last_command(exec_data, list, node));
	else
		return (setup_mid_command(exec_data, list, node));
	return (0);
}
