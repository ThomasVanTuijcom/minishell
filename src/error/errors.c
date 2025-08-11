/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:11:20 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/06 13:50:26 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *sys, char *cmd, char *arg, char *error)
{
	ft_putstr_fd(sys, STDERR);
	if (cmd)
		ft_putstr_fd(cmd, STDERR);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	ft_putstr_fd(error, STDERR);
}

void	err_exit_num_arg(t_data *data, char *content, t_p_node *node)
{
	if (!is_in_pipeline(node))
		ft_putstr_fd("exit\n", 2);
	ft_putstr_fd(MS_BASH, 2);
	ft_putstr_fd(MS_EXIT, 2);
	ft_putstr_fd(content, 2);
	ft_putstr_fd(ERR_NUM_ARG, 2);
	g_exit_code = 2;
	free_data(data);
	exit(g_exit_code);
}

void	print_quoted_error(char *sys, char *cmd, char *arg, char *error)
{
	ft_putstr_fd(sys, 2);
	ft_putstr_fd(cmd, 2);
	if (arg)
	{
		ft_putchar_fd('`', 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': ", 2);
	}
	ft_putstr_fd(error, 2);
}

void	print_bad_id_exp(t_p_node *node)
{
	print_quoted_error(MS_BASH, MS_EXPORT, node->content_exp_wq, ERR_ID);
	g_exit_code = 1;
}

void	print_error_and_exit(char *msg_error, t_data *data)
{
	ft_putstr_fd(msg_error, 2);
	ft_putstr_fd("\n", 2);
	free_data(data);
	exit(g_exit_code);
}
