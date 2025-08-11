/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_direct_path_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:56:08 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/24 16:13:18 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_path_prefix(char *str)
{
	int		i;
	int		j;
	char	*cleaned;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] > 32 && str[i] <= 126)
		i++;
	cleaned = malloc(sizeof(char) * (i + 1));
	if (!cleaned)
		return (NULL);
	j = 0;
	while (j < i)
	{
		cleaned[j] = str[j];
		j++;
	}
	cleaned[i] = '\0';
	return (cleaned);
}

int	is_direct_path_to_cmd(char *input, t_p_node *node)
{
	char	*clean_path;

	if (!input || !node)
		return (0);
	clean_path = extract_path_prefix(input);
	if (!clean_path)
		return (0);
	if (access(clean_path, F_OK) == 0 && (clean_path[0] == '/'
			|| clean_path[0] == '.'))
	{
		node->path = ft_strdup(input);
		free(clean_path);
		return (1);
	}
	free(clean_path);
	return (0);
}
