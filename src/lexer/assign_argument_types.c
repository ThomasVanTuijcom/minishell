/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_argument_types.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 12:57:14 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/11 17:28:14 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_heredoc_valid(t_p_node *node)
{
	t_p_node	*delim;

	if (!node || !node->next)
		return (0);
	delim = node->next;
	if (!delim->content || classify_as_meta(delim->content))
	{
		delim->token_type = INVALID_HEREDOC;
		return (0);
	}
	return (1);
}

int	handle_heredoc(t_p_node *node)
{
	if (!node || !node->next)
		return (0);
	node->next->token_type = LIMITATOR;
	is_heredoc_valid(node);
	if (!node->next->next)
		return (0);
	node->next->next->token_type = CMD;
	return (1);
}

void	handle_next_token(t_p_node *node)
{
	if (!node->next)
		return ;
	if (!ft_strcmp(node->content, "<"))
		node->next->token_type = INFILE;
	else if (!ft_strcmp(node->content, "<<"))
		handle_heredoc(node);
	else if (!ft_strcmp(node->content, ">"))
		node->next->token_type = OUTFILE;
	else if (!ft_strcmp(node->content, ">>"))
		node->next->token_type = APPEND_OF;
}

int	classify_meta_token(t_p_node *node)
{
	if (!ft_strcmp(node->content, "<"))
		node->token_type = REDIR_IN;
	else if (!ft_strcmp(node->content, "<<"))
		node->token_type = HEREDOC;
	else if (!ft_strcmp(node->content, ">"))
		node->token_type = REDIR_OUT;
	else if (!ft_strcmp(node->content, ">>"))
		node->token_type = APPEND;
	else if (!ft_strcmp(node->content, "|"))
		node->token_type = PIPE;
	else if (only_metachars(node->content) && !contains_metachar(node->content))
		node->token_type = WRONG_META;
	handle_next_token(node);
	return (0);
}

int	assign_argument_types(t_p_list *list)
{
	t_p_node	*curr;
	bool		file;

	curr = list->head;
	file = false;
	while (curr)
	{
		classify_meta_token(curr);
		curr = curr->next;
	}
	curr = list->head;
	while (curr)
	{
		if (curr->token_type == PIPE)
			file = false;
		if (curr->token_type == OUTFILE || curr->token_type == APPEND_OF)
			file = true;
		if (file && curr->content[0] == '-' && curr->content[1])
			curr->token_type = OPTION;
		curr = curr->next;
	}
	return (0);
}
