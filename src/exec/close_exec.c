/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:41:43 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/24 16:10:16 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_exec(t_p_node *node, t_p_list *list, int exec_data[5])
{
	if (node->fd[0] > 0)
		close(node->fd[0]);
	if (node->fd[1] > 0)
		close(node->fd[1]);
	if (exec_data[EXEC_INDEX] > 1)
		close(list->pipe[1]);
	if (node->prev && list->pipe[1] > 0 && node->prev->token_type == PIPE)
		close(list->pipe[1]);
	return (0);
}

int	close_exec_p(t_p_list *list, int exec_data[5])
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (i < plst_size(list))
	{
		if ((0 < waitpid(0, &status, 0) && (WIFEXITED(status))))
			g_exit_code = WEXITSTATUS(status);
		i++;
	}
	unlink(TMP_HEREDOC_FILE);
	close(exec_data[EXEC_STDIN_COPY]);
	close(exec_data[EXEC_STDOUT_COPY]);
	if (list->pipe[0] > 0)
		close(list->pipe[0]);
	if (list->pipe[1] > 0)
		close(list->pipe[1]);
	return (0);
}
