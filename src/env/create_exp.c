/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:49:19 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/06 18:10:15 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_env_nodes(t_env_node *a, t_env_node *b)
{
	char	*tmp_str;
	int		tmp_id;

	tmp_str = a->line;
	a->line = b->line;
	b->line = tmp_str;
	tmp_str = a->var;
	a->var = b->var;
	b->var = tmp_str;
	tmp_str = a->content;
	a->content = b->content;
	b->content = tmp_str;
	tmp_id = a->var_type;
	a->var_type = b->var_type;
	b->var_type = tmp_id;
	tmp_id = a->value_set;
	a->value_set = b->value_set;
	b->value_set = tmp_id;
}

void	sort_exp(t_env_list *list)
{
	t_env_node	*current;
	t_env_node	*next;
	int			sorted;

	if (!list || !list->head)
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		current = list->head;
		while (current && current->next)
		{
			next = current->next;
			if (ft_strcmp(current->var, next->var) > 0)
			{
				swap_env_nodes(current, next);
				sorted = 0;
			}
			current = current->next;
		}
	}
}

void	create_exp(t_data *data)
{
	t_env_node	*node;
	t_env_node	*curr;
	int			i;

	if (!data)
		return ;
	curr = data->env->head;
	i = 0;
	while (curr)
	{
		node = new_env_node(curr->line);
		if (!node)
		{
			free_env_list(data->exp);
			data->exp = NULL;
			return ;
		}
		env_list_addback(&data->exp, node);
		curr = curr->next;
		i++;
	}
	sort_exp(data->exp);
	g_exit_code = 0;
}
