/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praucq <praucq@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:55:35 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/30 13:51:37 by praucq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_variable_env(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

char	*set_content_env(char *str, t_env_node *node)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
	{
		node->value_set = 0;
		return (ft_strdup(""));
	}
	node->value_set = 1;
	return (ft_substr(str, i + 1, ft_strlen(str) - i - 1));
}

int	set_var_id(char *str)
{
	if (!ft_strcmp(str, "PWD"))
		return (PWD);
	else if (!ft_strcmp(str, "OLDPWD"))
		return (OLDPWD);
	else if (!ft_strcmp(str, "HOME"))
		return (HOME);
	else if (!ft_strcmp(str, "SHLVL"))
		return (SHLVL);
	else
		return (BASIC);
}

int	set_env_content(t_env_node *node, char *content)
{
	node->line = ft_strdup(content);
	if (!node->line)
		return (0);
	node->var = set_variable_env(node->line);
	if (!node->var)
	{
		free_content_env_node(node);
		return (0);
	}
	node->content = set_content_env(node->line, node);
	if (!node->content)
	{
		free_content_env_node(node);
		return (0);
	}
	node->trimmed = trim_interior_spaces(ft_strtrim(node->content, " "));
	if (!node->trimmed)
	{
		free_content_env_node(node);
		return (0);
	}
	node->var_type = set_var_id(node->var);
	return (1);
}
