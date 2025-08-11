/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:41:09 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/05 20:24:50 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_heredoc(t_data *data, int count, char **delimitors)
{
	int	i;

	i = 0;
	data->heredoc = malloc(sizeof(char *) * (count + 1));
	if (!data->heredoc)
		return (0);
	while (i < count)
	{
		if (!read_heredoc(&data->heredoc[i], delimitors[i]))
		{
			free_2d_array_n(data->heredoc, i);
			data->heredoc = NULL;
			return (0);
		}
		i++;
	}
	data->heredoc[i] = NULL;
	return (1);
}

char	**get_heredoc_delimiters(t_p_list *list, int count)
{
	t_p_node	*curr;
	char		**delimitors;
	int			i;

	delimitors = malloc(sizeof(char *) * (count + 1));
	if (!delimitors)
		return (NULL);
	curr = list->head;
	i = 0;
	while (curr)
	{
		if (curr->token_type == LIMITATOR)
		{
			delimitors[i] = ft_strdup(curr->content_exp_wq);
			if (!delimitors[i])
				return (NULL);
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
