/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:10:44 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/06 14:13:55 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_cmd(char **paths, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], cmd);
		if (!paths[i])
			return (0);
		free(tmp);
		i++;
	}
	return (1);
}

int	pathfinder(t_data *data)
{
	t_p_node	*curr;
	char		*path;
	char		**full_paths;

	curr = data->parser->head;
	remake_envp(data);
	path = search_path(data->envp);
	while (curr)
	{
		if (curr->token_type == CMD)
		{
			if (is_directory(curr->content_exp_wq))
			{
				print_error(MS_BASH, NULL, curr->content_exp_wq, ERR_IS_DIR);
				g_exit_code = 126;
				return (0);
			}
			full_paths = build_command_paths(path, curr->cmds[0]);
			if (!is_direct_path_to_cmd(curr->content_exp_wq, curr))
				resolve_command_path(full_paths, curr);
			free_2d_array(full_paths);
		}
		curr = curr->next;
	}
	return (0);
}
