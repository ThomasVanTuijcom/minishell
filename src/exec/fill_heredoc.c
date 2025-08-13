/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:59:00 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/13 16:56:55 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_child_process(int pipefd[2], char *delimiter)
{
	char	*heredoc_content;

	heredoc_content = NULL;
	close(pipefd[0]);
	heredoc_signal_handlers();
	if (!read_heredoc(&heredoc_content, delimiter))
	{
		free(heredoc_content);
		close(pipefd[1]);
		exit(1);
	}
	write(pipefd[1], heredoc_content, strlen(heredoc_content));
	free(heredoc_content);
	close(pipefd[1]);
	exit(0);
}

static int	handle_fork_error(int pipefd[2], t_data *data, int i)
{
	perror("fork");
	close(pipefd[0]);
	close(pipefd[1]);
	free_2d_array_n(data->heredoc, i);
	data->heredoc = NULL;
	return (0);
}

static int	create_heredoc_pipe(int pipefd[2], t_data *data, int i)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		free_2d_array_n(data->heredoc, i);
		data->heredoc = NULL;
		return (0);
	}
	return (1);
}

static int	allocate_heredoc_array(t_data *data, int count)
{
	data->heredoc = malloc(sizeof(char *) * (count + 1));
	if (!data->heredoc)
		return (0);
	return (1);
}

int	fill_heredoc(t_data *data, int count, char **delimitors)
{
	int		i;
	pid_t	pid;
	int		pipefd[2];

	if (!allocate_heredoc_array(data, count))
		return (0);
	i = 0;
	while (i < count)
	{
		if (!create_heredoc_pipe(pipefd, data, i))
			return (0);
		pid = fork();
		if (pid < 0)
			return (handle_fork_error(pipefd, data, i));
		else if (pid == 0)
			heredoc_child_process(pipefd, delimitors[i]);
		else
		{
			if (!heredoc_parent_process(data, i, pipefd, pid))
				return (0);
		}
		i++;
	}
	data->heredoc[i] = NULL;
	return (1);
}
