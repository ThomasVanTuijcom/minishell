/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_lines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:06:22 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/29 11:29:18 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable_value(char *var, t_env_list *env)
{
	t_env_node	*node;

	if (!var)
		return (ft_strdup(""));
	if (!ft_strcmp(var, "$"))
		return (ft_strdup("$"));
	if (!ft_strcmp(var, "?"))
		return (ft_itoa(g_exit_code));
	node = env->head;
	while (node)
	{
		if (!ft_strcmp(var, node->var))
			return (ft_strdup(node->content));
		node = node->next;
	}
	return (ft_strdup(""));
}

char	*add_content_exp_heredoc(char **str, char *result,
		t_env_list *env)
{
	char	*var;
	char	*content;

	var = extract_variable_name(str);
	content = expand_variable_value(var, env);
	result = ft_strjoin(result, content);
	free(content);
	free(var);
	return (result);
}

char	*expand_variables(char *line, t_env_list *env)
{
	char	*result;
	char	*ptr;

	result = NULL;
	ptr = line;
	while (*ptr)
	{
		if (*ptr == '$')
			result = add_content_exp_heredoc(&ptr, result, env);
		else
		{
			result = add_char_to_string(result, *ptr);
			ptr++;
		}
	}
	result = add_char_to_string(result, '\n');
	return (result);
}

char	**expand_heredoc_lines(char **lines, t_env_list *env)
{
	char	**result;
	char	*expanded;
	int		i;

	if (!lines)
		return (NULL);
	i = 0;
	while (lines[i])
		i++;
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (lines[i])
	{
		expanded = expand_variables(lines[i], env);
		if (!expanded)
		{
			free_2d_array(result);
			return (NULL);
		}
		result[i++] = expanded;
	}
	result[i] = NULL;
	return (result);
}
