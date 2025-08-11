/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:48:40 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/06 14:11:18 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ensure_trailing_slash(char **paths)
{
	int		i;
	char	*tmp;
	size_t	len;

	if (!paths)
		return (0);
	i = 0;
	while (paths[i])
	{
		len = ft_strlen(paths[i]);
		if (len == 0 || paths[i][len - 1] != '/')
		{
			tmp = ft_strjoin(paths[i], "/");
			if (!tmp)
			{
				free_2d_array(paths);
				return (0);
			}
			free(paths[i]);
			paths[i] = tmp;
		}
		i++;
	}
	return (1);
}

char	**build_command_paths(char *path_env, char *cmd)
{
	char	**dirs;

	if (!path_env || !cmd)
		return (NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	if (!ensure_trailing_slash(dirs))
	{
		free_2d_array(dirs);
		return (NULL);
	}
	if (!add_cmd(dirs, cmd))
	{
		free_2d_array(dirs);
		return (NULL);
	}
	return (dirs);
}
