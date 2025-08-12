/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cmd_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:42:05 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/12 18:51:29 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**gen_io_tab(t_p_node *infile, t_p_node *outfile)
{
	char	**content;

	content = malloc(sizeof(char *) * 3);
	if (!content)
		return (NULL);
	if (infile)
		content[0] = ft_strdup(infile->content_exp_wq);
	else
		content[0] = ft_strdup("");
	if (outfile)
		content[1] = ft_strdup(outfile->content_exp_wq);
	else
		content[1] = ft_strdup("");
	content[2] = NULL;
	return (content);
}

char	**cmd_io_paths(t_p_node *node)
{
	t_p_node	*curr;
	t_p_node	*infile;
	t_p_node	*outfile;

	curr = node;
	infile = NULL;
	outfile = NULL;
	while (curr && curr->token_type != PIPE)
	{
		if (curr->token_type == INFILE)
			infile = curr;
		else if (curr->token_type == OUTFILE)
			outfile = curr;
		curr = curr->prev;
	}
	curr = node;
	while (curr && curr->token_type != PIPE)
	{
		if (curr->token_type == INFILE || curr->token_type == LIMITATOR)
			infile = curr;
		else if (curr->token_type == OUTFILE || curr->token_type == APPEND_OF)
			outfile = curr;
		curr = curr->next;
	}
	return (gen_io_tab(infile, outfile));
}

int	setup_cmd_redirections(t_data *data, t_p_list *list)
{
	t_p_node	*curr;
	char		**fds;

	curr = list->head;
	while (curr)
	{
		if (curr->token_type == CMD)
		{
			fds = cmd_io_paths(curr);
			setup_io_redirections(data, curr, fds);
			if (fds)
				free_2d_array(fds);
			fds = NULL;
		}
		curr = curr->next;
	}
	return (1);
}
