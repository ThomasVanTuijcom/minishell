/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:29:16 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/13 21:28:17 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/* ************************************************************************** */
/*                            STRUCTURE DEFINITIONS                           */
/* ************************************************************************** */

enum					e_token_type
{
	APPEND,
	APPEND_OF,
	ASTERISQUE,
	CMD,
	CMP,
	CONTINUE,
	DOUBLE_PIPE,
	EMPTY,
	ERROR,
	INVALID_HEREDOC,
	HEREDOC,
	INFILE,
	LIMITATOR,
	LOGICAL_AND,
	OPTION,
	OPTION_CMD,
	OUTFILE,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	SIMPLE_ARG,
	VAR,
	WRONG_META
};

/* ************************************************************************** */
/*                            FUNCTION DECLARATIONS                           */
/* ************************************************************************** */

typedef struct s_p_node	t_p_node;

/*					INIT_LEXER.C					*/
int						init_lexer(t_data *data);
int						has_invalid_meta_sequence(t_p_list *list);
bool					pipe_followed_by_redir(t_p_node *curr);

/*					ASSIGN_ARGUMENT_TYPES.C				*/
int						is_heredoc_valid(t_p_node *node);
int						handle_heredoc(t_p_node *node);
void					handle_next_token(t_p_node *node);
int						classify_meta_token(t_p_node *node);
int						assign_argument_types(t_p_list *list);

/*					ASSIGN_ARGUMENT_CMD.C				*/
int						assign_command_roles(t_p_list *list);
void					classify_cmd_token(t_p_node *node, int *cmd_found);

/*					UTILS_LEXER.C				*/
int						contains_metachar(char *content);
int						only_metachars(char *str);
int						is_metachar_type(int type);
int						is_invalid_followup_token(char *content);
bool					classify_as_meta(const char *str);

#endif
