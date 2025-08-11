/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praucq <praucq@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:26:57 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/30 13:54:37 by praucq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

/* ************************************************************************** */
/*                            FUNCTION DECLARATIONS                           */
/* ************************************************************************** */

typedef struct s_data		t_data;
typedef struct s_env_node	t_env_node;

/*					GET_ENV.C					*/
void						create_env(t_data *data, char **envp);
void						create_exp(t_data *data);

/*					UTILS_ENV.C					*/
int							len_interior_spaces(char *str);
char						*trim_interior_spaces(char *str);

/*					SET_ENV.C					*/
char						*set_variable_env(char *str);
char						*set_content_env(char *str, t_env_node *node);
int							set_var_id(char *str);
int							set_env_content(t_env_node *node, char *content);

/*					SET_ENVP.C					*/
char						*search_path(char **envp);
char						*search_home(char **envp);
char						*search_pwd(char **envp);

void						sort_exp(t_env_list *list);

#endif
