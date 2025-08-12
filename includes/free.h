/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:12:41 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/12 18:23:00 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

/* ************************************************************************** */
/*                            FUNCTION DECLARATIONS                           */
/* ************************************************************************** */

typedef struct s_p_list	t_p_list;

/*					FREE.C					*/
void					free_2d_array_n(char **array, int count);
void					free_2d_array(char **arr);

/*					FREE_DATA.C					*/
void					free_data_buffers(t_data *data);
void					free_data_lists(t_data *data);
void					free_data(t_data *data);

/*					FREE_LIST.C					*/
void					free_env_list(t_env_list *list);
void					free_content_env_node(t_env_node *node);
void					free_p_list(t_p_list *list);
void					free_p_node(t_p_node *node);

/*					FREE_FD.C					*/
void					free_data_fd(t_data *data);

#endif
