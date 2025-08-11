/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:20:53 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/29 13:28:41 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env_list(t_env_list **list)
{
	*list = malloc(sizeof(t_env_list));
	if (!(*list))
		return (0);
	(*list)->head = NULL;
	(*list)->tail = NULL;
	(*list)->length = 0;
	return (1);
}

t_env_node	*new_env_node(char *content)
{
	t_env_node	*node;

	node = malloc(sizeof(t_env_node));
	if (!node)
		return (NULL);
	if (!set_env_content(node, content))
	{
		free(node);
		return (NULL);
	}
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	env_list_addback(t_env_list **list, t_env_node *node)
{
	if (!list || !node)
		return ;
	if (!list)
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
	(*list)->length++;
}

void	delete_env_node(t_env_list *list, t_env_node *node)
{
	if (!list || !node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	else
		list->head = node->next;
	if (node->next)
		node->next->prev = node->prev;
	else
		list->tail = node->prev;
	free(node->line);
	free(node->var);
	free(node->content);
	free(node->trimmed);
	free(node);
	list->length--;
}

t_env_node	*find_env_node_by_var(t_env_list *list, const char *var)
{
	t_env_node	*current;

	if (!list || !var)
		return (NULL);
	current = list->head;
	while (current)
	{
		if (current->var && ft_strcmp(current->var, var) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
