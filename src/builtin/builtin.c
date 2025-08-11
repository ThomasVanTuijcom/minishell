/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praucq <praucq@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:52:47 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/30 13:58:54 by praucq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_cleanup(int should_return, t_data *data, int exec_data[5])
{
	if (exec_data[EXEC_PIPE_FD] > 0)
		close(exec_data[EXEC_PIPE_FD]);
	if (exec_data[EXEC_TOTAL_CMDS] > 1)
	{
		close(0);
		close(1);
		close(exec_data[EXEC_STDIN_COPY]);
	}
	close(exec_data[EXEC_STDOUT_COPY]);
	if (data->parser->pipe[0])
		close(data->parser->pipe[0]);
	if (data->parser->pipe[1])
		close(data->parser->pipe[1]);
	reset_io(exec_data, data->parser, 1);
	if (should_return)
		return (0);
	free_data(data);
	exit(g_exit_code);
}

int	dispatch_builtin(t_data *data, t_p_node *node)
{
	if (!ft_strcmp(node->content_exp_wq, "exit"))
		ft_exit(data, node);
	else if (!ft_strcmp(node->content_exp_wq, "cd"))
		ft_cd(data, data->env, node);
	else if (!ft_strcmp(node->content_exp_wq, "export"))
		ft_export(data, node, data->exp);
	else if (!ft_strcmp(node->content_exp_wq, "env"))
		ft_env(node, data->env);
	else if (!ft_strcmp(node->content_exp_wq, "pwd"))
		ft_pwd(node, data);
	else if (!ft_strcmp(node->content_exp_wq, "unset"))
		ft_unset(data, node);
	else if (!ft_strcmp(node->content_exp_wq, "echo"))
		ft_echo(node);
	else
		return (-1);
	return (0);
}

int	exec_builtin(t_data *data, t_p_node *node, int n, int exec_data[5])
{
	if (!node)
		return (0);
	if (dispatch_builtin(data, node) == -1)
		return (-1);
	return (exit_cleanup(n, data, exec_data));
}
