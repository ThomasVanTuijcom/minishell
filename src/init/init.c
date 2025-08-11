/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praucq <praucq@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:29:06 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/29 18:49:04 by praucq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_all(t_data *data, char **envp)
{
	create_env(data, envp);
	create_exp(data);
	data->path = search_path(envp);
	data->pwd = search_pwd(envp);
	data->home = search_home(envp);
}

void	init_all(t_data *data, char **envp)
{
	g_exit_code = 0;
	data->buffer = NULL;
	data->env = NULL;
	data->exp = NULL;
	data->heredoc = NULL;
	data->delimitators = NULL;
	data->parser = NULL;
	data->path = NULL;
	data->pwd = NULL;
	data->home = NULL;
	data->envp = NULL;
	data->expired_envp = 1;
	set_all(data, envp);
}

void	reset_env_node(t_env_node *node)
{
	node->line = NULL;
	node->var = NULL;
	node->content = NULL;
	node->trimmed = NULL;
	node->var_type = 0;
}
