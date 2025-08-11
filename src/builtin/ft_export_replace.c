/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_replace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:46:12 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/24 17:19:34 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_existing_var_exp(t_data *data, t_env_list *export, char *var,
		int check)
{
	t_env_node	*node;
	char		*variable;

	if (!export || !var)
		return ;
	variable = set_variable_env(var);
	if (!variable)
		print_error_and_exit(ERR_MALLOC, data);
	node = export->head;
	while (node)
	{
		if (!ft_strcmp(variable, node->var))
		{
			free_content_env_node(node);
			reset_env_node(node);
			set_new_content_in_export(node, var, data, check);
			break ;
		}
		node = node->next;
	}
	free(variable);
}

int	check_existing_var(t_env_list *env, char *var)
{
	t_env_node	*node;
	char		*target_var;

	if (!env || !var)
		return (0);
	target_var = set_variable_env(var);
	if (!target_var)
		return (0);
	node = env->head;
	while (node)
	{
		if (!ft_strcmp(target_var, node->var))
		{
			free(target_var);
			return (1);
		}
		node = node->next;
	}
	free(target_var);
	return (0);
}

void	replace_existing_var(t_data *args, t_env_list *env, char *var)
{
	t_env_node	*node;
	char		*variable;

	node = NULL;
	node = env->head;
	variable = set_variable_env(var);
	while (node)
	{
		if (!ft_strcmp(variable, node->var))
		{
			free_content_env_node(node);
			reset_env_node(node);
			set_new_content_in_env(node, var, args);
		}
		node = node->next;
	}
	free(variable);
}
