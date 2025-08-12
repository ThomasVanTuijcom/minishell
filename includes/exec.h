/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:38:11 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/12 18:48:17 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/* ************************************************************************** */
/*                            STRUCTURE DEFINITIONS                           */
/* ************************************************************************** */

enum						e_exec_data
{
	EXEC_INDEX,
	EXEC_TOTAL_CMDS,
	EXEC_PIPE_FD,
	EXEC_STDIN_COPY,
	EXEC_STDOUT_COPY
};

/* ************************************************************************** */
/*                            FUNCTION DECLARATIONS                           */
/* ************************************************************************** */

typedef struct s_p_node		t_p_node;
typedef struct s_p_list		t_p_list;
typedef struct s_env_list	t_env_list;

/*					HEREDOC.C				*/
char						**get_heredoc_delimiters(t_p_list *list, int count);
int							count_heredocs(t_p_list *list);

/*					FILL_HEREDOC.C				*/
int							fill_heredoc(t_data *data, int count,
								char **delimitors);

/*					READ_HEREDOC.C				*/
char						*read_line_from_stdin(void);
int							collect_heredoc_lines(char **result,
								const char *delimitor_nl);
int							read_heredoc(char **heredoc, char *delimitor);

/*					INIT_EXEC.C				*/
int							executor(t_data *data);

/*					HANDLE_HEREDOC_VARIABLES.C				*/
int							contains_quotes(char *str);
int							get_total_length(char **lines);
char						*join_lines(char **lines);
int							handle_heredoc_variables(char **hdoc,
								char *limitator, t_env_list *env);

/*					EXPAND_HEREDOC_LINES.C				*/
char						*expand_variable_value(char *var, t_env_list *env);
char						*add_content_exp_heredoc(char **str, char *result,
								t_env_list *env);
char						*expand_variables(char *line, t_env_list *env);
char						**expand_heredoc_lines(char **lines,
								t_env_list *env);

/*					BUILD_ARGS_COUNT.C				*/
int							count_cmd_args(t_p_node *node);
int							*build_cmd_args_counts(t_p_list *list, int size);

/*					ASSIGN_CMD_OPTIONS.C				*/
int							count_cmd_nodes(t_p_list *list);
int							fill_cmd_args_array(t_p_node *node, char **argv,
								int start_index, int limit);
char						**build_cmd_args_array(t_p_node *cmd_node,
								int arg_count);
int							assign_args_to_cmds(t_p_list *list,
								int *arg_counts);
int							assign_cmd_options(t_p_list *list);

/*					PATH.C				*/
int							pathfinder(t_data *data);
int							add_cmd(char **paths, char *cmd);

/*					BUILD_CMD_PATH.C				*/
int							ensure_trailing_slash(char **paths);
char						**build_command_paths(char *path_env, char *cmd);

/*					IS_DIRECT_PATH_CMD.C				*/
char						*extract_path_prefix(char *str);
int							is_direct_path_to_cmd(char *input, t_p_node *node);

/*					RESOLVE_CMD_PATH.C				*/
int							is_directory(char *path);
int							starts_with_special_char(char c);
int							is_builtin_command(t_p_node *node);
char						*find_existing_cmd_path(char **path_candidates);
void						resolve_command_path(char **cmd_path_candidates,
								t_p_node *node);

/*					CREATE_FILES.C				*/
int							verify_input_file(char *filename);
int							create_output_file(char *filename);
int							create_files(t_p_list *list);

/*					SETUP_CMD_REDIRECTIONS.C				*/
char						**gen_io_tab(t_p_node *infile, t_p_node *outfile);
char						**cmd_io_paths(t_p_node *node);
int							setup_cmd_redirections(t_data *data,
								t_p_list *list);

/*					SETUP_IO_REDIRECTIONS.C				*/
int							count_hdocs(char **hdocs);
void						setup_io_redirections(t_data *data, t_p_node *node,
								char **fds);

/*					EXECUTE_CMD.C				*/
int							execute_cmd(t_data *data, t_p_list *list);
int							reset_io(int exec_data[5], t_p_list *list, int n);

/*					EXECUTE_MINISHELL.C				*/
void						execute_minishell(t_data *data, char *path,
								char **cmds, char **envp);

/*					EXECUTE_NODE.C				*/
int							dup_close(int exec_data[5]);
int							execution(t_p_node *node, t_data *data,
								int exec_data[5]);
void						duplicate_process(int exec_data[5], t_p_node *node,
								t_data *data);
int							fork_exec(int exec_data[5], t_p_node *node,
								t_data *data);
void						execute_node(int exec_data[5], t_p_node *node,
								t_data *data);

/*					DUPLICATING.C				*/
int							close_return(int datas[5], t_p_list *list);
int							close_all(int exec_data[5], t_p_list *list);
int							setup_last_command(int exec_data[5], t_p_list *list,
								t_p_node *node);
int							duplicating(int exec_data[5], t_p_list *list,
								t_p_node *node);

/*					SETUP_FIRST_COMMAND.C				*/
int							setup_first_command(int exec_data[5],
								t_p_list *list, t_p_node *node);
int							close_first_cmd(int datas[5], t_p_list *list);

/*					SETUP_MID_COMMAND.C				*/
int							setup_mid_command(int exec_data[5], t_p_list *list,
								t_p_node *node);

/*					CLOSE_EXEC.C				*/
int							close_exec(t_p_node *node, t_p_list *list,
								int exec_data[5]);
int							close_exec_p(t_p_list *list, int exec_data[5]);

/*					HANDLE_REDIRECTIONS.C				*/
t_p_node					*get_first_node_in_pipeline(t_p_node *node);
void						handle_input_redirection(t_data *data,
								t_p_node *node, t_p_node *curr, bool *input);
void						handle_output_redirection(t_p_node *node,
								t_p_node *curr, bool *output);

/*					HEREDOC_PARENT_PROCESS.C				*/
int							heredoc_parent_process(t_data *data, int i,
								int pipefd[2], pid_t pid);

#endif
