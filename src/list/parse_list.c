/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:34:53 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/29 15:52:58 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_parse_list(t_p_list **list)
{
	if (!list)
		return (0);
	*list = malloc(sizeof(t_p_list));
	if (!*list)
		return (0);
	(*list)->head = NULL;
	(*list)->tail = NULL;
	(*list)->pipe[0] = 0;
	(*list)->pipe[1] = 0;
	(*list)->pid = -1;
	return (1);
}

t_p_node	*new_p_node(char *str)
{
	t_p_node	*node;

	node = malloc(sizeof(t_p_node));
	if (!node)
		return (NULL);
	node->content = ft_strdup(str);
	node->content_exp = NULL;
	node->content_exp_wq = NULL;
	node->new_content = NULL;
	node->next = NULL;
	node->prev = NULL;
	node->has_quote = false;
	node->q_meta_indexes = NULL;
	node->token_type = EMPTY;
	node->cmds = NULL;
	node->path = NULL;
	node->index = -1;
	node->fd[0] = 0;
	node->fd[1] = 0;
	return (node);
}

void	p_list_addback(t_p_list **list, t_p_node *node)
{
	if (!list || !node)
		return ;
	if (!*list)
		return ;
	if (!(*list)->head)
	{
		(*list)->head = node;
		(*list)->tail = node;
	}
	else
	{
		(*list)->tail->next = node;
		node->prev = (*list)->tail;
		(*list)->tail = node;
	}
	node->index = plst_size(*list);
}

void	p_list_addbetween(t_p_list **list, t_p_node *after, t_p_node *node)
{
	if (!list || !*list || !after || !node)
		return ;
	node->prev = after;
	node->next = after->next;
	if (after->next)
		after->next->prev = node;
	else
		(*list)->tail = node;
	after->next = node;
}

void	del_p_node(t_p_list **list, t_p_node *node_to_delete)
{
	t_p_node	*curr;

	if (!list || !node_to_delete)
		return ;
	if (node_to_delete->prev)
		node_to_delete->prev->next = node_to_delete->next;
	else
		(*list)->head = node_to_delete->next;
	if (node_to_delete->next)
		node_to_delete->next->prev = node_to_delete->prev;
	else
		(*list)->tail = node_to_delete->prev;
	curr = node_to_delete->next;
	free(node_to_delete->content);
	free(node_to_delete->content_exp);
	free(node_to_delete->content_exp_wq);
	free(node_to_delete);
	while (curr)
	{
		curr->index--;
		curr = curr->next;
	}
}
