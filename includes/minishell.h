/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praucq <praucq@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:19:39 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/31 16:20:00 by praucq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "./builtin.h"
# include "./env.h"
# include "./errors.h"
# include "./exec.h"
# include "./free.h"
# include "./init.h"
# include "./lexer.h"
# include "./list.h"
# include "./parser.h"
# include "./signals.h"
# include "./utils.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <limits.h>

# define PROMPT "$> "
# define METACHARS "|<>&"
# define BUFFER_SIZE 1024
# define TMP_HEREDOC_FILE "/tmp/.sh-hd-eyhd6c"

extern int	g_exit_code;

#endif
