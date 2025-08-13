/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:41:09 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/13 21:45:53 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_heredoc_delimiters(t_p_list *list, int count)
{
	t_p_node	*curr;
	char		**delimitors;
	int			i;
	char		*trimmed;

	delimitors = malloc(sizeof(char *) * (count + 1));
	if (!delimitors)
		return (NULL);
	curr = list->head;
	i = 0;
	while (curr)
	{
		if (curr->token_type == LIMITATOR)
		{
			trimmed = ft_strtrim(curr->content, "\"\'");
			delimitors[i] = ft_strdup(trimmed);
			if (!delimitors[i])
				return (NULL);
			free(trimmed);
			i++;
		}
		curr = curr->next;
	}
	delimitors[i] = NULL;
	return (delimitors);
}

int	count_heredocs(t_p_list *list)
{
	t_p_node	*curr;
	int			count;

	count = 0;
	curr = list->head;
	while (curr)
	{
		if (curr->token_type == LIMITATOR)
			count++;
		curr = curr->next;
	}
	return (count);
}
