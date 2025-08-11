/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:04:40 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/06 13:58:52 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(char *path)
{
	DIR	*dir_ptr;

	dir_ptr = opendir(path);
	if (dir_ptr || errno == EACCES)
	{
		if (dir_ptr)
			closedir(dir_ptr);
		return (1);
	}
	return (0);
}

int	starts_with_special_char(char c)
{
	return (c == ':' || c == '#' || c == '!');
}

/*
	0: not builtin
	1: builtin can't be forked
	2: builtin can be forked
*/
int	is_builtin_command(t_p_node *node)
{
	const char	*cmd = node->content_exp_wq;

	if (!node || !node->content_exp_wq)
		return (-1);
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd,
			"unset") || !ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd,
			"echo"))
		return (2);
	return (0);
}

char	*find_existing_cmd_path(char **path_candidates)
{
	int	i;

	i = 0;
	if (!path_candidates)
	{
		return (NULL);
	}
	while (path_candidates[i])
	{
		if (!access(path_candidates[i], F_OK))
			return (path_candidates[i]);
		i++;
	}
	return (NULL);
}

void	resolve_command_path(char **cmd_path_candidates, t_p_node *node)
{
	char	*path;

	path = find_existing_cmd_path(cmd_path_candidates);
	if (!path)
	{
		node->path = NULL;
		if (!is_builtin_command(node)
			&& !starts_with_special_char(node->content_exp_wq[0]))
		{
			if (is_directory(node->content_exp_wq))
			{
				print_error(MS_BASH, NULL, node->content_exp_wq, ERR_IS_DIR);
				g_exit_code = 126;
			}
			else
			{
				print_error(MS_BASH, NULL, node->content_exp_wq, ERR_CMD);
				g_exit_code = 127;
			}
		}
		else if (!ft_strcmp("!", node->content_exp_wq))
			g_exit_code = 1;
	}
	else
		node->path = ft_strdup(path);
}
