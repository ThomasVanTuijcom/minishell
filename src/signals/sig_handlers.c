/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:45:19 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/13 16:58:34 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_segfault(int signal)
{
	if (signal == SIGSEGV)
	{
		ft_putstr_fd("Segmentation fault (core dumped)\n", 1);
		exit(139);
	}
}

void	sig_ignore(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		g_exit_code = 130;
	}
	if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 1);
		g_exit_code = 131;
	}
}

void	sig_new_line(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_code = 130;
	}
}

void	sig_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		g_exit_code = 130;
		exit(g_exit_code);
	}
}
