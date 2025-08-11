/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:52:31 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/11 12:41:51 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_signal_handlers(void)
{
	signal(SIGINT, &sig_new_line);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGSEGV, &sig_segfault);
}

void	modify_signal_handlers(void)
{
	signal(SIGINT, &sig_ignore);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGQUIT, &sig_ignore);
}

void	heredoc_signal_handlers(void)
{
	signal(SIGINT, &sig_heredoc);
	signal(SIGQUIT, &sig_heredoc);
}

void	disable_sigpipe_handler(void)
{
	signal(SIGPIPE, SIG_DFL);
}

void    disable_signal_handling(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGPIPE, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
}
