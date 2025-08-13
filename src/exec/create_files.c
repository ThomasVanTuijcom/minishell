/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:13:02 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/13 19:03:45 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_input_file(char *filename)
{
	if (access(filename, F_OK) != 0)
	{
		print_error(MS_BASH, NULL, filename, ERR_NO_FOD);
		g_exit_code = 1;
		return (0);
	}
	return (1);
}

int	create_output_file(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT, 0664);
	if (fd < 0)
	{
		print_error(MS_BASH, NULL, filename, ERR_NO_CREATE);
		return (0);
	}
	close(fd);
	return (1);
}

int	create_files(t_p_list *list)
{
	t_p_node	*curr;

	if (!list)
		return (0);
	curr = list->head;
	while (curr)
	{
		if (curr->token_type == INFILE)
		{
			if (!verify_input_file(curr->content_exp_wq))
				return (0);
		}
		else if (curr->token_type == OUTFILE
			|| curr->token_type == APPEND_OF)
		{
			if (!create_output_file(curr->content_exp_wq))
				return (0);
		}
		curr = curr->next;
	}
	return (1);
}
