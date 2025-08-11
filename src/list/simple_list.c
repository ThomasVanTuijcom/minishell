/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:25:18 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/24 16:46:48 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*new_lst_node(char *str)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->str = ft_strdup(str);
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

int	lst_size(t_list *list)
{
	int	length;

	length = 0;
	if (!list)
		return (0);
	while (list)
	{
		length++;
		list = list->next;
	}
	return (length);
}

t_list	*lst_last_node(t_list *list)
{
	if (!list)
		return (NULL);
	if (!list->next)
		return (list);
	while (list->next)
	{
		list = list->next;
	}
	return (list);
}

void	lst_add_back(t_list **list, t_list *new)
{
	t_list	*last;

	last = lst_last_node(*list);
	if (!last)
		*list = new;
	else
	{
		last->next = new;
		new->prev = last;
	}
}

void	lst_del_one(t_list **list, t_list *node_to_delete)
{
	if (!list || !*list || !node_to_delete)
		return ;
	if (node_to_delete->prev)
		node_to_delete->prev->next = node_to_delete->next;
	else
		*list = node_to_delete->next;
	if (node_to_delete->next)
		node_to_delete->next->prev = node_to_delete->prev;
	free(node_to_delete->str);
	free(node_to_delete);
}
