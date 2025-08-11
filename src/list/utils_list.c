/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:51:42 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/16 12:03:05 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	plst_size(t_p_list *list)
{
	int			length;
	t_p_node	*curr;

	length = 0;
	if (!list)
		return (0);
	curr = list->head;
	while (curr)
	{
		length++;
		curr = curr->next;
	}
	return (length);
}
