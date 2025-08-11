/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mid_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:23:07 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/07 21:28:42 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_mid_out(int exec_data[5], t_p_list *list, t_p_node *node)
{
	if (node->fd[1] > 0)
	{
		if (dup2(node->fd[1], STDOUT_FILENO) < 0)
			return (-1);
		close(list->pipe[0]);
		close(list->pipe[1]);
		close(exec_data[EXEC_PIPE_FD]);
	}
	else
	{
		if (dup2(list->pipe[1], STDOUT_FILENO) < 0)
			return (-1);
		close(list->pipe[1]);
		close(exec_data[EXEC_STDIN_COPY]);
		close(exec_data[EXEC_STDOUT_COPY]);
	}
	return (0);
}

int	setup_mid_command(int exec_data[5], t_p_list *list, t_p_node *node)
{
	if (node->fd[0] > 0 && dup2(node->fd[0], STDIN_FILENO) < 0)
		return (close_return(exec_data, list));
	else
	{
		if (dup2(exec_data[EXEC_PIPE_FD], STDIN_FILENO) < 0)
			return (close_return(exec_data, list));
		close(exec_data[EXEC_PIPE_FD]);
		close(list->pipe[0]);
	}
	if (setup_mid_out(exec_data, list, node) == -1)
		return (close_return(exec_data, list));
	return (0);
}
