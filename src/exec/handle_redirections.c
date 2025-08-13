/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:17:50 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/13 19:23:15 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_p_node	*get_first_node_in_pipeline(t_p_node *node)
{
	while (node && node->prev && node->prev->token_type != PIPE)
		node = node->prev;
	return (node);
}

static void	open_infile(t_p_node *node, t_p_node *curr, bool *input)
{
	if (*input && node->fd[0] > 0)
		close(node->fd[0]);
	node->fd[0] = open(curr->content_exp_wq, O_RDONLY);
	*input = true;
}

static void	open_heredoc(t_data *data, t_p_node *node, bool *input)
{
	int	heredoc_index;

	if (*input && node->fd[0] > 0)
		close(node->fd[0]);
	heredoc_index = count_hdocs(data->heredoc) - 1;
	node->fd[0] = open(TMP_HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (node->fd[0] > 0)
	{
		ft_putstr_fd(data->heredoc[heredoc_index], node->fd[0]);
		close(node->fd[0]);
	}
	node->fd[0] = open(TMP_HEREDOC_FILE, O_RDONLY);
	if (node->fd[0] < 0)
		perror("open heredoc tmp file");
	*input = true;
}

void	handle_input_redirection(t_data *data, t_p_node *node, t_p_node *curr,
		bool *input)
{
	if (curr->token_type == INFILE)
		open_infile(node, curr, input);
	else if (curr->token_type == HEREDOC)
		open_heredoc(data, node, input);
}

void	handle_output_redirection(t_p_node *node, t_p_node *curr, bool *output)
{
	if (curr->token_type == OUTFILE)
	{
		if (*output && node->fd[1] > 0)
			close(node->fd[1]);
		node->fd[1] = open(curr->content_exp_wq, O_WRONLY | O_CREAT | O_TRUNC,
				0664);
		*output = true;
	}
	else if (curr->token_type == APPEND_OF)
	{
		if (*output && node->fd[1] > 0)
			close(node->fd[1]);
		node->fd[1] = open(curr->content_exp_wq, O_WRONLY | O_CREAT | O_APPEND,
				0664);
		*output = true;
	}
}
