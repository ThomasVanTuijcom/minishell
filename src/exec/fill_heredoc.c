/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:59:00 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/11 19:06:50 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_heredoc(t_data *data, int count, char **delimitors)
{
	int		i;
	pid_t	pid;
	int		status;
	int		pipefd[2];
	char	*heredoc_content;
	char	buffer[4096];
	ssize_t	len;

	data->heredoc = malloc(sizeof(char *) * (count + 1));
	if (!data->heredoc)
		return (0);
	for (i = 0; i < count; i++)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			free_2d_array_n(data->heredoc, i);
			data->heredoc = NULL;
			return (0);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			close(pipefd[0]);
			close(pipefd[1]);
			free_2d_array_n(data->heredoc, i);
			data->heredoc = NULL;
			return (0);
		}
		else if (pid == 0)
		{
			// --- CHILD process ---
			close(pipefd[0]);        // close read end
			signal(SIGINT, SIG_DFL); // default signals
			signal(SIGQUIT, SIG_DFL);
			heredoc_content = NULL;
			if (!read_heredoc(&heredoc_content, delimitors[i]))
			{
				free(heredoc_content);
				close(pipefd[1]);
				_exit(1);
			}
			// Write heredoc content to pipe
			write(pipefd[1], heredoc_content, strlen(heredoc_content));
			free(heredoc_content);
			close(pipefd[1]);
			_exit(0);
		}
		else
		{
			// --- PARENT process ---
			close(pipefd[1]); // close write end
			// Read heredoc content from pipe
			len = read(pipefd[0], buffer, sizeof(buffer) - 1);
			if (len < 0)
			{
				perror("read");
				close(pipefd[0]);
				free_2d_array_n(data->heredoc, i);
				data->heredoc = NULL;
				return (0);
			}
			buffer[len] = '\0';
			data->heredoc[i] = strdup(buffer);
			close(pipefd[0]);
			waitpid(pid, &status, 0);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			{
				free_2d_array_n(data->heredoc, i + 1);
				data->heredoc = NULL;
				return (0); // Ctrl-C pressed during heredoc
			}
			if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
			{
				free_2d_array_n(data->heredoc, i + 1);
				data->heredoc = NULL;
				return (0); // heredoc read failed
			}
		}
	}
	data->heredoc[i] = NULL;
	return (1);
}
