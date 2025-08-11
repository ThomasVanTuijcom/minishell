/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:41:20 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/07 16:13:00 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_export_variable(t_data *data, t_p_node *node, int id_check,
		bool *has_error)
{
	if (id_check == 0)
	{
		*has_error = true;
		print_bad_id_exp(node);
		g_exit_code = 1;
		return ;
	}
	if (id_check == 3)
	{
		append_to_current_value(data, node);
		id_check = 1;
	}
	export_var_to_export(data, data->exp, node->content_exp_wq, id_check);
	export_var_to_env(data, data->env, node->content_exp_wq, id_check);
	data->expired_envp = 1;
}

int	check_identifier_export(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0' || ft_isdigit(str[0]) || (!ft_isalpha(str[0])
			&& str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (str[i] == '=')
		return (1);
	else if (str[i] == '+')
	{
		if (str[i + 1] == '=')
			return (3);
		return (0);
	}
	else
		return (2);
}

void	handle_export_argument(t_data *data, t_p_node *node, bool *export_alone,
		bool *has_error)
{
	int	id_check;

	id_check = check_identifier_export(node->content_exp_wq);
	*export_alone = false;
	if (node->token_type == OPTION)
	{
		print_option_invalid(node, MS_EXPORT);
		return ;
	}
	if (node->token_type == SIMPLE_ARG || node->token_type == OPTION)
		process_export_variable(data, node, id_check, has_error);
}

void	display_export(t_env_list *export)
{
	t_env_node	*curr;

	curr = NULL;
	if (export)
		curr = export->head;
	while (curr)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(curr->var, 1);
		if (curr->value_set)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(curr->content, 1);
			ft_putstr_fd("\"", 1);
		}
		write(1, "\n", 1);
		curr = curr->next;
	}
}

void	ft_export(t_data *data, t_p_node *node, t_env_list *exp)
{
	t_p_node	*curr;
	bool		has_error;
	bool		is_export_alone;

	curr = node->next;
	has_error = false;
	is_export_alone = true;
	curr = skip_faulty_nodes(curr);
	if (!curr)
	{
		display_export(exp);
		g_exit_code = 0;
		return ;
	}
	while (curr && curr->token_type != PIPE)
	{
		handle_export_argument(data, curr, &is_export_alone, &has_error);
		curr = curr->next;
		curr = skip_faulty_nodes(curr);
	}
	if (is_export_alone)
		display_export(exp);
	if (!has_error)
		g_exit_code = 0;
}
