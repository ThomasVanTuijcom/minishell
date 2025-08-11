/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:45:44 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/11 12:46:41 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_minishell(t_data *data, char *path, char **cmds, char **envp)
{
	int		launching;
	pid_t	pid;
	int		nested_exit_code;

	nested_exit_code = 0;
	remake_envp(data);
	disable_signal_handling();
	pid = fork();
	if (pid == 0)
	{
		if (!is_directory(path))
			launching = execve(path, cmds, envp);
		else
			launching = -1;
		if (launching == -1)
		{
			print_error(MS_BASH, NULL, path, ERR_CMD);
			g_exit_code = 127;
		}
		exit(g_exit_code);
	}
	waitpid(pid, &nested_exit_code, 0);
	g_exit_code = nested_exit_code / 256;
	modify_signal_handlers();
}
