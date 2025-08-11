/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:53:20 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/07 12:38:31 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdbool.h>
/* ************************************************************************** */
/*                            STRUCTURE DEFINITIONS                           */
/* ************************************************************************** */

/* ************************************************************************** */
/*                            FUNCTION DECLARATIONS                           */
/* ************************************************************************** */

typedef struct s_p_node		t_p_node;
typedef struct s_p_list		t_p_list;
typedef struct s_env_list	t_env_list;
typedef struct s_env_node	t_env_node;
typedef struct s_data		t_data;

/*					BUILTIN.C				*/
int							dispatch_builtin(t_data *data, t_p_node *node);
int							exec_builtin(t_data *data, t_p_node *node, int n,
								int exec_data[5]);
int							exit_cleanup(int should_return, t_data *data,
								int exec_data[5]);

/*					FT_EXIT.C				*/
bool						is_in_pipeline(t_p_node *node);
bool						is_too_long_for_ull(char *content);
void						exit_with_argument(t_data *data, char *content,
								t_p_node *arg);
void						ft_exit(t_data *data, t_p_node *cmd);

/*					FT_ECHO.C				*/
int							is_valid_echo_option(const char *str);
t_p_node					*skip_n_options(t_p_node *node,
								int *suppress_newline);
void						print_argument(const char *arg, int *first,
								const char *arg_with_quotes);
void						ft_echo(t_p_node *parser);

/*					FT_PWD.C				*/
void						update_pwd_in_env_list(t_env_list *list,
								const char *new_pwd);
void						change_pwd_env(char *new_pwd, t_env_list *env);
void						change_pwd_export(char *new_pwd,
								t_env_list *export);
void						ft_pwd(t_p_node *node, t_data *data);

/*					FT_UNSET.C				*/
int							is_invalid_identifier(const char *str);
void						handle_unset_argument(t_data *data, t_p_node *node,
								bool *error);
void						ft_unset(t_data *data, t_p_node *node);

/*					FT_EXPORT.C				*/
void						process_export_variable(t_data *data,
								t_p_node *node, int id_check, bool *has_error);
int							check_identifier_export(char *str);
void						handle_export_argument(t_data *data, t_p_node *node,
								bool *export_alone, bool *has_error);
void						display_export(t_env_list *export);
void						ft_export(t_data *data, t_p_node *node,
								t_env_list *exp);

/*					FT_EXPORT_UTILS.C				*/
void						set_new_content_in_env(t_env_node *node,
								char *content, t_data *args);
void						set_new_content_in_export(t_env_node *node,
								char *content, t_data *args, int check);
void						create_node_to_export_or_env(t_env_node *node,
								t_env_list *list);
void						append_to_current_value(t_data *data,
								t_p_node *node);

/*					FT_EXPORT_REPLACE.C				*/
void						replace_existing_var_exp(t_data *data,
								t_env_list *export, char *var, int check);
int							check_existing_var(t_env_list *env, char *var);
void						replace_existing_var(t_data *args, t_env_list *env,
								char *var);

/*					FT_EXPORT_ASSIGN.C				*/
void						export_var_to_env(t_data *data, t_env_list *env,
								char *var, int check);
void						export_var_to_export(t_data *data,
								t_env_list *export, char *var, int check);

/*					FT_CD.C				*/
void						handle_cd_error(t_p_node *node, int error_type,
								bool *error);
int							count_simple_args(t_p_node *node);
void						handle_cd_target(t_data *data, t_p_node *node,
								char *oldpwd, bool *error);
bool						process_cd_argument(t_data *data, t_p_node *node,
								char *oldpwd, bool *error);
void						ft_cd(t_data *args, t_env_list *env,
								t_p_node *node);

/*					FT_CD_PATHS.C				*/
void						cd_to_oldpwd(t_data *args, t_env_list *env,
								char *oldpwd, bool *error);
void						cd_home(t_data *args, t_env_list *env, char *oldpwd,
								bool *error);
void						change_directory(t_data *args, char *oldpwd,
								char *path, bool *error);
void						cd_to_home_append(t_data *data, char *oldpwd,
								bool *error, char *arg);

/*					FT_CD_UPDATE.C				*/
void						update_oldpwd_in_env_list(t_env_list *list,
								const char *new_pwd);
void						change_oldpwd_env(char *new_pwd, t_env_list *env);
void						change_oldpwd_export(char *new_pwd,
								t_env_list *export);
void						update_env(char *pwd, char *oldpwd, t_data *data);

/*					FT_ENV.C				*/
void						display_env(t_env_node *node);
void						ft_env(t_p_node *node, t_env_list *list);
#endif
