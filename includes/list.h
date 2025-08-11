/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praucq <praucq@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:08:17 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/30 13:52:04 by praucq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stdbool.h>

/* ************************************************************************** */
/*                            STRUCTURE DEFINITIONS                           */
/* ************************************************************************** */

typedef struct s_list
{
	char				*str;
	struct s_list		*prev;
	struct s_list		*next;
}						t_list;

typedef struct s_p_node
{
	char				*content;
	char				*content_exp;
	char				*content_exp_wq;
	char				*new_content;
	int					*q_meta_indexes;
	bool				has_quote;
	int					index;
	char				**cmds;
	char				*path;
	int					fd[2];
	enum e_token_type	token_type;
	struct s_p_node		*prev;
	struct s_p_node		*next;
}						t_p_node;

typedef struct s_p_list
{
	struct s_p_node		*head;
	struct s_p_node		*tail;
	int					pipe[2];
	int					pid;
}						t_p_list;

enum					e_var_type
{
	BASIC,
	PWD,
	OLDPWD,
	HOME,
	SHLVL,
};

typedef struct s_env_node
{
	char				*line;
	char				*var;
	enum e_var_type		var_type;
	char				*content;
	char				*trimmed;
	int					value_set;
	struct s_env_node	*prev;
	struct s_env_node	*next;
}						t_env_node;

typedef struct s_env_list
{
	t_env_node			*head;
	t_env_node			*tail;
	int					length;
}						t_env_list;

/* ************************************************************************** */
/*                            FUNCTION DECLARATIONS                           */
/* ************************************************************************** */

/*					SIMPLE_LIST.C					*/
t_list					*new_lst_node(char *str);
int						lst_size(t_list *list);
t_list					*lst_last_node(t_list *list);
void					lst_add_back(t_list **list, t_list *new);
void					lst_del_one(t_list **list, t_list *node_to_delete);

/*					PARSE_LIST.C					*/
int						init_parse_list(t_p_list **list);
t_p_node				*new_p_node(char *str);
void					p_list_addback(t_p_list **list, t_p_node *node);
void					p_list_addbetween(t_p_list **list, t_p_node *after,
							t_p_node *node);
void					del_p_node(t_p_list **list, t_p_node *node_to_delete);

/*					ENV_LIST.C					*/
int						init_env_list(t_env_list **list);
t_env_node				*new_env_node(char *content);
void					env_list_addback(t_env_list **list, t_env_node *node);
void					delete_env_node(t_env_list *list, t_env_node *node);
t_env_node				*find_env_node_by_var(t_env_list *list,
							const char *var);

/*					UTILS_LIST.C					*/
int						plst_size(t_p_list *list);

#endif
