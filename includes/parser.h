/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:43:51 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/11 17:41:53 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

# define QUOTE_MARKER_SINGLE 6 // ACK
# define QUOTE_MARKER_DOUBLE 8 // BS

/* ************************************************************************** */
/*                            STRUCTURE DEFINITIONS                           */
/* ************************************************************************** */

typedef struct s_list	t_list;

typedef struct s_data
{
	t_env_list			*env;
	t_env_list			*exp;
	t_p_list			*parser;
	char				*buffer;
	char				*path;
	char				*pwd;
	char				*home;
	char				**delimitators;
	char				**heredoc;
	char				**envp;
	int					expired_envp;
}						t_data;

/* ************************************************************************** */
/*                            FUNCTION DECLARATIONS                           */
/* ************************************************************************** */

/*					ADD_CONTENT.C					*/
char					*check_put_content_of_expand(char *var,
							t_env_node *node, t_p_node *pars);
char					*get_content_expand(char *var, t_env_list *env,
							t_p_node *pars);
void					add_string_to_content_exp(char **str, t_p_node *node,
							t_env_list *env);
void					add_char_to_content_exp(char **str, t_p_node *node);
void					put_content_exp_wq(t_p_node *node, int *i, int *j,
							char quote);

/*					EXPAND_FROM_ENV.C					*/
char					*indic_quotes_in_content(char *content, t_p_node *node);
char					*match_and_expand_variable(char *var, t_env_node *node,
							t_p_node *pars);
char					*expand_variable_from_env(char *var, t_env_list *env,
							t_p_node *pars);

/*					EXPAND_PARSER_CONTENT.C					*/
void					process_expanded_string_quotes(t_p_node *node);
char					*restore_q_from_markers(char *content);
void					expand_parser_content(char *str, t_p_node *tail,
							t_env_list *env);

/*					EXTRACT_VAR.C					*/
void					calc_var_length(int *count, int *i, char *str);
int						get_var_length(char *str);
char					*extract_variable_name(char **str);

/*					INIT_PARSER.C					*/
void					remove_quotes_from_word(char *content, t_p_node *node);
int						split_content(t_p_list *parser, t_env_list *env);
void					process_parser_tail(t_p_node *tail, t_env_list *env,
							t_data *data);
void					init_parser(t_data *data);

/*					MASK_QUOTED_METACHARS.C			*/
void					skip_quoted_string(const char *str, int *i, int *j,
							t_p_node *node);
int						fill_index_meta(char *str, t_p_node *node);
int						count_metachars_inside_double_quotes(char *str);
void					mask_content(char *str, int amount, t_p_node *node);
int						mask_quoted_metachars(char *content, t_p_node *node);

/*					PARSE_AND_EXPAND_DOLLARS.C			*/
void					expand_and_append_trimmed_var(char **str, t_p_node *psr,
							t_env_list *env);
void					parse_and_expand_dollars(char **str, t_p_node *node,
							t_env_list *env);

/*					PARSE_QUOTE_CONTENT.C			*/
void					parse_single_quote_content(char **str, t_p_node *node);
void					parse_double_quote_content(char **str, t_p_node *node,
							t_env_list *env);

/*					PARSE_WORD.C			*/
int						parse_word(char **line, t_p_list **parser);
int						check_length_of_word(char *word);
int						get_len_word_in_quotes(char quote, char *line, int *pos,
							int length);

/*					UNCLOSED_QUOTES.C			*/
int						get_unclosed_quote_type(char *str);
int						check_for_unclosed_quotes(char *str);

/*					UTILS_PARSER.C			*/
int						contains_unquoted_meta(char *str);
int						get_word_length(char *word);
int						skip_spaces(char **line);
char					*copy_word_without_quotes(char **src, char *dest);
int						get_len_in_quotes(char quote, char *line, int *pos,
							int length);

#endif
