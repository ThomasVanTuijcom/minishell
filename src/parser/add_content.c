/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:10:14 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/29 11:58:36 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_put_content_of_expand(char *var, t_env_node *node,
		t_p_node *pars)
{
	char	*content;

	if (!ft_strcmp(var, "$"))
		return (ft_strdup("$"));
	if (!ft_strcmp(var, "?"))
		return (ft_itoa(g_exit_code));
	if (!ft_strcmp(var, node->var))
	{
		content = ft_strdup(node->content);
		return (indic_quotes_in_content(content, pars));
	}
	return (NULL);
}

char	*get_content_expand(char *var, t_env_list *env, t_p_node *pars)
{
	t_env_node	*node;

	if (!ft_strcmp(var, "$"))
		return (ft_strdup("$"));
	if (!ft_strcmp(var, "?"))
		return (ft_itoa(g_exit_code));
	node = env->head;
	while (node)
	{
		if (!ft_strcmp(var, node->var))
			return (check_put_content_of_expand(var, node, pars));
		node = node->next;
	}
	return (ft_strdup(""));
}

void	add_string_to_content_exp(char **str, t_p_node *node, t_env_list *env)
{
	char	*var;
	char	*content;
	char	*tmp;

	var = extract_variable_name(str);
	content = get_content_expand(var, env, node);
	tmp = node->content_exp;
	node->content_exp = ft_strjoin(node->content_exp, content);
	free(tmp);
	free(content);
	free(var);
}

void	add_char_to_content_exp(char **str, t_p_node *node)
{
	node->content_exp = add_char_to_string(node->content_exp, **str);
	(*str)++;
}

void	put_content_exp_wq(t_p_node *node, int *i, int *j, char quote)
{
	(*i)++;
	while (node->content_exp[*i] && node->content_exp[*i] != quote)
		node->content_exp_wq[(*j)++] = node->content_exp[(*i)++];
	(*i)++;
}
