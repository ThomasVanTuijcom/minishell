/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 15:55:30 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/12 18:27:04 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data_buffers(t_data *data)
{
	if (data->buffer)
	{
		free(data->buffer);
		data->buffer = NULL;
	}
	if (data->delimitators)
	{
		free_2d_array(data->delimitators);
		data->delimitators = NULL;
	}
	if (data->heredoc)
	{
		free_2d_array(data->heredoc);
		data->heredoc = NULL;
	}
	if (data->envp)
	{
		free_2d_array(data->envp);
		data->envp = NULL;
	}
}

void	free_data_lists(t_data *data)
{
	if (data->env)
	{
		free_env_list(data->env);
		data->env = NULL;
	}
	if (data->exp)
	{
		free_env_list(data->exp);
		data->exp = NULL;
	}
	if (data->parser)
	{
		free_p_list(data->parser);
		data->parser = NULL;
	}
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	free_data_lists(data);
	free_data_buffers(data);
	//free_data_fd(data);
}
