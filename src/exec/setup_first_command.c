/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_first_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:50:11 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/07 20:41:25 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_first_command_wp(int exec_data[5], t_p_list *list, t_p_node *node)
{
	if (node->fd[0] > 0 && dup2(node->fd[0], STDIN_FILENO) < 0)
		return (-1);
	if (node->fd[1] > 0 && dup2(node->fd[1], STDOUT_FILENO) < 0)
		return (-1);
	else if (list->pipe[1] > 0 && dup2(list->pipe[1], STDOUT_FILENO) < 0)
		return (-1);
	if (node->fd[0] > 1)
		close(node->fd[0]);
	if (node->fd[1] > 1)
		close(node->fd[1]);
	close(exec_data[EXEC_STDIN_COPY]);
	close(exec_data[EXEC_STDOUT_COPY]);
	return (1);
}

int	setup_first_command(int exec_data[5], t_p_list *list, t_p_node *node)
{
	if (exec_data[EXEC_TOTAL_CMDS] > 1)
	{
		if (node->fd[0] > 0 && dup2(node->fd[0], STDIN_FILENO) < 0)
			return (close_return(exec_data, list));
		if (node->fd[1] > 0 && dup2(node->fd[1], STDOUT_FILENO) < 0)
			return (close_return(exec_data, list));
		else if (node->fd[1] == 0 && dup2(list->pipe[1], STDOUT_FILENO) < 0)
			return (close_return(exec_data, list));
		close(list->pipe[0]);
		if (exec_data[EXEC_PIPE_FD] > 0)
			close(exec_data[EXEC_PIPE_FD]);
		if (node->fd[0] > 0)
			close(node->fd[0]);
		if (node->fd[1] > 0)
			close(node->fd[1]);
		close(exec_data[EXEC_STDIN_COPY]);
		close(exec_data[EXEC_STDOUT_COPY]);
	}
	else if (setup_first_command_wp(exec_data, list, node) == -1)
		return (close_return(exec_data, list));
	return (0);
}
