/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:58:23 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/29 16:02:26 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_p_node(t_p_node *node)
{
	if (!node)
		return ;
	if (node->content)
		free(node->content);
	if (node->content_exp)
		free(node->content_exp);
	if (node->content_exp_wq)
		free(node->content_exp_wq);
	if (node->new_content)
		free(node->new_content);
	if (node->q_meta_indexes)
		free(node->q_meta_indexes);
	if (node->cmds)
		free_2d_array(node->cmds);
	if (node->path)
		free(node->path);
	free(node);
}

void	free_p_list(t_p_list *list)
{
	t_p_node	*current;
	t_p_node	*next;

	if (!list)
		return ;
	current = list->head;
	while (current)
	{
		next = current->next;
		free_p_node(current);
		current = next;
	}
	free(list);
}

void	free_env_list(t_env_list *list)
{
	t_env_node	*current;
	t_env_node	*next;

	if (!list)
		return ;
	current = list->head;
	while (current)
	{
		next = current->next;
		free_content_env_node(current);
		free(current);
		current = next;
	}
	free(list);
}

void	free_content_env_node(t_env_node *node)
{
	if (node->line)
		free(node->line);
	if (node->var)
		free(node->var);
	if (node->content)
		free(node->content);
	if (node->trimmed)
		free(node->trimmed);
}
