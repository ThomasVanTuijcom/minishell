/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:30:40 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/13 21:41:08 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_in_exec(t_data *data)
{
	free_2d_array(data->delimitators);
	data->delimitators = NULL;
	free_2d_array(data->heredoc);
	data->heredoc = NULL;
}

int	executor(t_data *data)
{
	int	nbr_hdocs;

	nbr_hdocs = count_heredocs(data->parser);
	data->delimitators = get_heredoc_delimiters(data->parser, nbr_hdocs);
	if (!fill_heredoc(data, nbr_hdocs, data->delimitators))
	{
		free_in_exec(data);
		return (0);
	}
	if (nbr_hdocs > 0)
		handle_heredoc_variables(data->heredoc, data->delimitators[nbr_hdocs
			- 1], data->env);
	else
		handle_heredoc_variables(data->heredoc, NULL, data->env);
	assign_cmd_options(data->parser);
	pathfinder(data);
	create_files(data->parser);
	setup_cmd_redirections(data, data->parser);
	if (data->parser->head->content_exp_wq[0])
		execute_cmd(data, data->parser);
	else if (ft_strlen(data->parser->head->content_exp)
		!= ft_strlen(data->parser->head->content_exp_wq))
		ft_putstr_fd("bash: : command not found\n", 2);
	free_in_exec(data);
	return (0);
}
