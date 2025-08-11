/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:04:17 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/24 16:07:20 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_lost_dir(char *pwd)
{
	ft_putstr_fd("pwd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	perror(pwd);
	g_exit_code = 1;
}

void	print_err_lost_dir(char *oldpwd, char *command, bool *error)
{
	ft_putstr_fd("chdir: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	perror(oldpwd);
	print_error(MS_BASH, MS_CD, command, ERR_STALE);
	g_exit_code = 1;
	*error = true;
}

void	print_option_invalid(t_p_node *node, char *cmd)
{
	print_error(MS_BASH, cmd, node->content_exp_wq, ERR_OPTION);
	g_exit_code = 2;
}
