/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parent_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 18:47:16 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/13 16:57:38 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc_exit_status(t_data *data, int i, int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		free_2d_array_n(data->heredoc, i + 1);
		data->heredoc = NULL;
		return (0);
	}
	if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
	{
		free_2d_array_n(data->heredoc, i + 1);
		data->heredoc = NULL;
		return (0);
	}
	return (1);
}

static int	handle_heredoc_read_error(t_data *data, int pipefd[2], int i)
{
	perror("read");
	close(pipefd[0]);
	free_2d_array_n(data->heredoc, i);
	data->heredoc = NULL;
	return (0);
}

int	heredoc_parent_process(t_data *data, int i, int pipefd[2], pid_t pid)
{
	char	buffer[4096];
	ssize_t	len;
	int		status;

	close(pipefd[1]);
	disable_signal_handling();
	len = read(pipefd[0], buffer, sizeof(buffer) - 1);
	if (len < 0)
		return (handle_heredoc_read_error(data, pipefd, i));
	buffer[len] = '\0';
	data->heredoc[i] = strdup(buffer);
	close(pipefd[0]);
	waitpid(pid, &status, 0);
	modify_signal_handlers();
	if (!handle_heredoc_exit_status(data, i, status))
		return (0);
	return (1);
}
