/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 09:41:07 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/07 14:55:41 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes_from_word(char *content, t_p_node *node)
{
	int	length;

	length = get_word_length(content);
	node->new_content = malloc(sizeof(char) * (length + 1));
	if (!node->new_content)
		return ;
	node->new_content = copy_word_without_quotes(&content, node->new_content);
}

int	split_content(t_p_list *parser, t_env_list *env)
{
	int			i;
	char		**splitted;
	t_p_node	*old_tail;

	splitted = NULL;
	splitted = ft_split_charset(splitted, parser->tail->content, METACHARS);
	if (!splitted)
		return (0);
	i = 0;
	old_tail = parser->tail;
	while (splitted[i])
	{
		p_list_addback(&parser, new_p_node(splitted[i]));
		expand_parser_content(parser->tail->content, parser->tail, env);
		remove_quotes_from_word(parser->tail->content, parser->tail);
		mask_quoted_metachars(parser->tail->content, parser->tail);
		i++;
	}
	del_p_node(&parser, old_tail);
	free_2d_array(splitted);
	return (0);
}

void	process_parser_tail(t_p_node *tail, t_env_list *env, t_data *data)
{
	if (contains_unquoted_meta(tail->content))
		split_content(data->parser, env);
	else
	{
		expand_parser_content(tail->content, tail, env);
		remove_quotes_from_word(tail->content, tail);
		mask_quoted_metachars(tail->content, tail);
	}
}

void	init_parser(t_data *data)
{
	char	*cpy;
	char	*tmp;
	int		i;
	int		len;

	if (!data->buffer[0])
		return ;
	tmp = ft_strdup(data->buffer);
	if (!tmp)
		return ;
	cpy = tmp;
	len = ft_strlen(cpy);
	i = 0;
	i += skip_spaces(&cpy);
	while (*cpy && i < len)
	{
		i += parse_word(&cpy, &data->parser);
		i += skip_spaces(&cpy);
		process_parser_tail(data->parser->tail, data->env, data);
	}
	free(tmp);
	return ;
}
