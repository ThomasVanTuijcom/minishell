/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:13:27 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/06 17:45:01 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define CD_ERR_INVALID_OPTION 1
# define CD_ERR_TOO_MANY_ARGS 2

# define MS_BASH "bash: "
# define MS_EXIT "exit: "
# define MS_PWD "pwd: "
# define MS_UNSET "unset: "
# define MS_EXPORT "export: "
# define MS_CD "cd: "
# define MS_ENV "env: "
# define ERR_NO_FOD "No such file or directory\n"
# define ERR_NO_CREATE "Cannot create file\n"
# define ERR_IS_DIR "Is a directory\n"
# define ERR_CMD "command not found\n"
# define ERR_UNCLOSED "bash: syntax error: unclosed quotes `"
# define ERR_TOKEN "bash: syntax error near unexpected token `"
# define ERR_NUM_ARG ": numeric argument required\n"
# define ERR_TOO_MANY_ARG "too many arguments\n"
# define ERR_OPTION "invalid option\n"
# define ERR_ID "not a valid identifier\n"
# define ERR_NOENV "No such environment\n"
# define ERR_MALLOC "Failed to allocate memory.\n"
# define ERR_HOME "HOME not set\n"
# define ERR_STALE "Stale file handle\n"
# define ERR_OLDPWD_NULL "OLDPWD not set\n"

/* ************************************************************************** */
/*                            FUNCTION DECLARATIONS                           */
/* ************************************************************************** */

typedef struct s_p_list	t_p_list;

/*					ERRORS.C					*/
void					print_error(char *sys, char *cmd, char *arg,
							char *error);
void					err_exit_num_arg(t_data *data, char *content,
							t_p_node *node);
void					print_quoted_error(char *sys, char *cmd, char *arg,
							char *error);
void					print_bad_id_exp(t_p_node *node);
void					print_error_and_exit(char *msg_error, t_data *data);

/*					ERRORS_SYNTAX.C					*/
void					print_syntax_error(char *msg, char *syntax);
int						print_syntax_error_meta(char *sign);
int						syntax_error_meta(t_p_list *list);

/*					ERRORS_CD.C					*/
void					print_err_lost_dir(char *oldpwd, char *command,
							bool *error);
void					print_error_lost_dir(char *pwd);
void					print_option_invalid(t_p_node *node, char *cmd);

#endif
