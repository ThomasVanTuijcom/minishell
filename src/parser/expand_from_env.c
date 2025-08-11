/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_from_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:18:22 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/06 15:50:51 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*indic_quotes_in_content(char *content, t_p_node *node)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = ft_strdup(content);
	free(content);
	while (cpy[i])
	{
		if (is_quote(cpy[i]) == 1)
		{
			cpy[i] = QUOTE_MARKER_SINGLE;
			node->has_quote = true;
		}
		else if (is_quote(cpy[i]) == 2)
		{
			cpy[i] = QUOTE_MARKER_DOUBLE;
			node->has_quote = true;
		}
		i++;
	}
	return (cpy);
}

char	*match_and_expand_variable(char *var, t_env_node *node, t_p_node *pars)
{
	char	*content;

	if (!var)
		return (NULL);
	if (!ft_strcmp(var, "$"))
		return (ft_strdup("$"));
	if (!ft_strcmp(var, "?"))
		return (ft_itoa(g_exit_code));
	if (!ft_strcmp(var, node->var))
	{
		content = ft_strdup(node->trimmed);
		return (indic_quotes_in_content(content, pars));
	}
	return (NULL);
}

char	*expand_variable_from_env(char *var, t_env_list *env, t_p_node *pars)
{
	char		*content;
	t_env_node	*node;

	node = env->head;
	while (node)
	{
		content = match_and_expand_variable(var, node, pars);
		if (content)
			return (content);
		node = node->next;
	}
	return (ft_strdup(""));
}
