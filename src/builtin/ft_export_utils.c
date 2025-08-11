/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:46:28 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/06 20:59:20 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_new_content_in_env(t_env_node *node, char *content, t_data *args)
{
	try_free(node->line);
	node->line = ft_strdup(content);
	if (!node->line)
		print_error_and_exit(ERR_MALLOC, args);
	try_free(node->var);
	node->var = set_variable_env(node->line);
	if (!node->var)
		print_error_and_exit(ERR_MALLOC, args);
	try_free(node->content);
	node->content = set_content_env(node->line, node);
	if (!node->content)
		print_error_and_exit(ERR_MALLOC, args);
	try_free(node->trimmed);
	node->trimmed = ft_strtrim(node->content, " ");
	node->trimmed = trim_interior_spaces(node->trimmed);
	if (!node->trimmed)
		print_error_and_exit(ERR_MALLOC, args);
	node->var_type = set_var_id(node->var);
}

void	create_node_to_export_or_env(t_env_node *node, t_env_list *list)
{
	if (list->head == NULL)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		node->prev = list->tail;
		list->tail->next = node;
		list->tail = node;
	}
}

void	set_new_content_in_export(t_env_node *node, char *content, t_data *args,
		int check)
{
	try_free(node->line);
	node->line = ft_strdup(content);
	if (!node->line)
		print_error_and_exit(ERR_MALLOC, args);
	try_free(node->var);
	node->var = set_variable_env(node->line);
	if (!node->var)
		print_error_and_exit(ERR_MALLOC, args);
	if (check == 1)
	{
		try_free(node->content);
		node->content = set_content_env(node->line, node);
		if (!node->content)
			print_error_and_exit(ERR_MALLOC, args);
		try_free(node->trimmed);
		node->trimmed = ft_strtrim(node->content, " ");
		if (!node->trimmed)
			print_error_and_exit(ERR_MALLOC, args);
	}
	node->var_type = set_var_id(node->var);
}

void	append_to_p_node(t_p_node *node, t_env_node *to_mod, int i, char *new)
{
	char	*tmp;

	if (!new)
		return ;
	tmp = NULL;
	new = ft_strjoin_and_replace(new, "=");
	if (new && to_mod)
		new = ft_strjoin_and_replace(new, to_mod->content);
	if (new)
		tmp = ft_strdup(&node->content_exp_wq[i + 2]);
	if (new && tmp)
		new = ft_strjoin_and_replace(new, tmp);
	if (tmp)
		free(tmp);
	if (new)
	{
		free(node->content_exp_wq);
		node->content_exp_wq = new;
	}
	if (!new)
		g_exit_code = 12;
}

void	append_to_current_value(t_data *data, t_p_node *node)
{
	char		*tmp;
	int			i;
	t_env_node	*to_modify;

	to_modify = data->exp->head;
	i = -1;
	while (node->content_exp_wq[++i] != '+')
		i++;
	tmp = ft_substr(node->content_exp_wq, 0, i);
	if (!tmp)
	{
		g_exit_code = 12;
		return ;
	}
	while (to_modify && tmp)
	{
		if (!ft_strcmp(tmp, to_modify->var))
			break ;
		to_modify = to_modify->next;
	}
	append_to_p_node(node, to_modify, i, tmp);
}
