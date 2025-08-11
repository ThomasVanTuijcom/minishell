/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praucq <praucq@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:43:30 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/30 17:52:30 by praucq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_invalid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0' || ft_isdigit(str[0]))
		return (1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	handle_unset_argument(t_data *data, t_p_node *node, bool *error)
{
	char		*var;
	t_env_node	*var_node;

	var = node->content_exp_wq;
	if (node->token_type == OPTION)
	{
		print_option_invalid(node, MS_UNSET);
		*error = true;
	}
	else
	{
		data->expired_envp = 1;
		var_node = find_env_node_by_var(data->env, var);
		delete_env_node(data->env, var_node);
		var_node = find_env_node_by_var(data->exp, var);
		delete_env_node(data->exp, var_node);
	}
}

void	ft_unset(t_data *data, t_p_node *node)
{
	t_p_node	*curr;
	bool		error;

	curr = node->next;
	error = false;
	while (curr && curr->token_type != PIPE)
	{
		if (curr->token_type == SIMPLE_ARG || curr->token_type == OPTION)
			handle_unset_argument(data, curr, &error);
		curr = curr->next;
	}
	if (!error)
		g_exit_code = 0;
}
