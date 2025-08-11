/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_assign.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praucq <praucq@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:46:23 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/30 17:26:04 by praucq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_var_to_env(t_data *data, t_env_list *env, char *var, int check)
{
	t_env_node	*node;

	if (!env)
		return ;
	if (check == 2)
		return ;
	if (check_existing_var(env, var))
	{
		replace_existing_var(data, env, var);
		return ;
	}
	node = new_env_node(var);
	set_new_content_in_env(node, var, data);
	create_node_to_export_or_env(node, env);
	env->length++;
}

void	export_var_to_export(t_data *data, t_env_list *export, char *var,
		int check)
{
	t_env_node	*new_node;

	if (!export)
		return ;
	if (check_existing_var(export, var))
	{
		if (check != 2)
			replace_existing_var_exp(data, export, var, check);
		return ;
	}
	new_node = new_env_node(var);
	set_new_content_in_export(new_node, var, data, check);
	create_node_to_export_or_env(new_node, export);
	sort_exp(export);
	export->length++;
}
