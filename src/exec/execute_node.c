/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:27:45 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/13 18:34:22 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_close(int exec_data[5])
{
	dup2(exec_data[EXEC_STDIN_COPY], STDIN_FILENO);
	dup2(exec_data[EXEC_STDOUT_COPY], STDOUT_FILENO);
	close(exec_data[EXEC_STDIN_COPY]);
	close(exec_data[EXEC_STDOUT_COPY]);
	return (0);
}

int	execution(t_p_node *node, t_data *data, int exec_data[5])
{
	int	err_code;

	err_code = 0;
	if (is_builtin_command(node))
		exec_builtin(data, node, exec_data[EXEC_TOTAL_CMDS], exec_data);
	else
	{
		if (node->path)
		{
			remake_envp(data);
			disable_sigpipe_handler();
			execve(node->path, node->cmds, data->envp);
			modify_signal_handlers();
			if (errno == 2)
				err_code = 127;
			else if (errno == 13)
				err_code = 126;
			print_error(MS_BASH, NULL, *node->cmds, strerror(errno));
			ft_putchar_fd('\n', 2);
			free_data(data);
			exit(err_code);
		}
	}
	return (0);
}

void	duplicate_process(int exec_data[5], t_p_node *node, t_data *data)
{
	duplicating(exec_data, data->parser, node);
	if (node->fd[0] >= 0 && node->fd[1] >= 0)
		execution(node, data, exec_data);
}

int	fork_exec(int exec_data[5], t_p_node *node, t_data *data)
{
	data->parser->pid = 0;
	if (exec_data[EXEC_TOTAL_CMDS] > 1 && pipe(data->parser->pipe) < 0)
		return (-1);
	data->parser->pid = fork();
	if (data->parser->pid == -1)
		return (-1);
	else if (data->parser->pid == 0)
	{
		duplicate_process(exec_data, node, data);
		free_data(data);
		exit(g_exit_code);
	}
	reset_io(exec_data, data->parser, 2);
	return (0);
}

void	execute_node(int exec_data[5], t_p_node *node, t_data *data)
{
	if (exec_data[EXEC_TOTAL_CMDS] == 1 && (is_minishell(node->content_exp_wq)
			|| !ft_strcmp(node->content_exp_wq, "bash")))
		execute_minishell(data, node->content_exp_wq, node->cmds, data->envp);
	else if (is_builtin_command(node) == 0 || is_builtin_command(node) == 2
		|| (is_builtin_command(node) == 1 && exec_data[EXEC_TOTAL_CMDS] > 1))
		fork_exec(exec_data, node, data);
	else
		duplicate_process(exec_data, node, data);
	if (exec_data[EXEC_TOTAL_CMDS] == 1 && is_builtin_command(node))
		dup_close(exec_data);
}
