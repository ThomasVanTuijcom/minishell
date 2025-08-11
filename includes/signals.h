/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:38:32 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/07 21:00:18 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/* ************************************************************************** */
/*                            STRUCTURE DEFINITIONS                           */
/* ************************************************************************** */

/* ************************************************************************** */
/*                            FUNCTION DECLARATIONS                           */
/* ************************************************************************** */

/*					SIG_HANDLERS.C				*/
void	sig_segfault(int signal);
void	sig_ignore(int signal);
void	sig_new_line(int signal);
void	sig_heredoc(int signal);

/*					SIG_SETUP.C				*/
void	setup_signal_handlers(void);
void	modify_signal_handlers(void);
void	heredoc_signal_handlers(void);
void	disable_sigpipe_handler(void);

#endif
