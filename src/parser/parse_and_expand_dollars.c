/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_expand_dollars.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:59:55 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/06 16:05:20 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_and_append_trimmed_var(char **str, t_p_node *psr,
		t_env_list *env)
{
	char	*var;
	char	*content;
	char	*tmp;

	var = NULL;
	content = NULL;
	var = extract_variable_name(str);
	content = expand_variable_from_env(var, env, psr);
	tmp = psr->content_exp;
	psr->content_exp = ft_strjoin(psr->content_exp, content);
	free(tmp);
	free(content);
	free(var);
}

void	parse_and_expand_dollars(char **str, t_p_node *node, t_env_list *env)
{
	int	i;
	int	length;

	i = 0;
	length = ft_strlen(*str);
	while (**str && i < length)
	{
		if (is_quote(**str) == 1)
			parse_single_quote_content(str, node);
		else if (is_quote(**str) == 2)
			parse_double_quote_content(str, node, env);
		else if (**str == '$' && is_quote(*(*str + 1)))
			(*str)++;
		else if (**str == '$')
			expand_and_append_trimmed_var(str, node, env);
		else
			add_char_to_content_exp(str, node);
		i++;
	}
	return ;
}
