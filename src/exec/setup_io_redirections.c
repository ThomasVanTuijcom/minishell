/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_io_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:42:00 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/07 21:53:55 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_hdocs(char **hdocs)
{
	int	count;

	if (!hdocs)
		return (0);
	count = 0;
	while (hdocs[count])
		count++;
	return (count);
}

int	get_input_type(t_p_node *node)
{
	t_p_node	*curr;
	int			type;

	type = 0;
	curr = node;
	while (curr && curr->token_type != PIPE)
	{
		if (curr->token_type == INFILE)
			type = 1;
		else if (curr->token_type == HEREDOC)
			type = 2;
		curr = curr->prev;
	}
	curr = node;
	while (curr && curr->token_type != PIPE)
	{
		if (curr->token_type == INFILE)
			type = 1;
		else if (curr->token_type == HEREDOC)
			type = 2;
		curr = curr->next;
	}
	return (type);
}

int	get_output_type(t_p_node *node)
{
	t_p_node	*curr;
	int			type;

	curr = node;
	type = 0;
	while (curr && curr->token_type != PIPE)
	{
		if (curr->token_type == OUTFILE)
			type = 1;
		else if (curr->token_type == APPEND_OF)
			type = 2;
		curr = curr->prev;
	}
	curr = node;
	while (curr && curr->token_type != PIPE)
	{
		if (curr->token_type == OUTFILE)
			return (1);
		else if (curr->token_type == APPEND_OF)
			return (2);
		curr = curr->next;
	}
	return (type);
}

void	setup_io_redirections(t_data *data, t_p_node *node, char **fds)
{
	int	heredoc_index;
	int	io_types[2];

	if (!fds)
		return ;
	io_types[0] = get_input_type(node);
	io_types[1] = get_output_type(node);
	if (io_types[0] == 1 && fds[0])
		node->fd[0] = open(fds[0], O_RDONLY);
	else if (io_types[0] == 2 && fds[0])
	{
		heredoc_index = count_hdocs(data->heredoc) - 1;
		node->fd[0] = open(TMP_HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC,
				0664);
		if (node->fd[0] > 0)
			ft_putstr_fd(data->heredoc[heredoc_index], node->fd[0]);
		close(node->fd[0]);
		node->fd[0] = open(TMP_HEREDOC_FILE, O_RDONLY | O_CREAT, 0664);
	}
	if (io_types[1] == 1 && fds[1])
		node->fd[1] = open(fds[1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (io_types[1] == 2 && fds[1])
		node->fd[1] = open(fds[1], O_WRONLY | O_CREAT | O_APPEND, 0664);
}
