/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:26:07 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/07 21:04:05 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_in_pipeline(t_p_node *node)
{
	t_p_node	*tmp;

	tmp = node;
	while (tmp)
	{
		if (tmp->token_type == PIPE)
			return (true);
		tmp = tmp->next;
	}
	tmp = node->prev;
	while (tmp)
	{
		if (tmp->token_type == PIPE)
			return (true);
		tmp = tmp->prev;
	}
	return (false);
}

bool	is_too_long_for_ull(char *content)
{
	int	i;
	int	digit_count;

	i = 0;
	digit_count = 0;
	if (content[i] == '+' || content[i] == '-')
		i++;
	while (content[i])
	{
		if (!ft_isdigit(content[i]))
			return (true);
		digit_count++;
		i++;
	}
	return (digit_count > 19);
}

void	exit_with_argument(t_data *data, char *content, t_p_node *cmd)
{
	unsigned long long	ull_value;
	long long			final_value;
	bool				is_negative;

	if (!content || !*content)
		err_exit_num_arg(data, content, cmd);
	is_negative = (content[0] == '-');
	if (is_too_long_for_ull(content))
		err_exit_num_arg(data, content, cmd);
	if (*content == '+' || *content == '-')
		content++;
	ull_value = ft_atoull(content);
	if ((!is_negative && ull_value > LLONG_MAX) || (is_negative
			&& ull_value > 9223372036854775808uLL))
		err_exit_num_arg(data, content, cmd);
	if (is_negative)
		final_value = -((long long)ull_value);
	else
		final_value = (long long)ull_value;
	g_exit_code = (unsigned char)(final_value % 256);
	if (!is_in_pipeline(cmd))
		ft_putstr_fd("exit\n", 2);
	free_data(data);
	exit(g_exit_code);
}

void	ft_exit(t_data *data, t_p_node *cmd)
{
	t_p_node	*arg;

	arg = cmd->next;
	if (arg && (arg->token_type == SIMPLE_ARG || arg->token_type == OPTION))
	{
		if (!is_only_digits(arg->content_exp_wq))
			err_exit_num_arg(data, arg->content_exp_wq, cmd);
		if (arg->next && arg->next->token_type != PIPE)
		{
			if (!(arg->next->next) || (arg->next->next
					&& arg->next->next->token_type != PIPE))
				if (!is_in_pipeline(cmd))
					ft_putstr_fd("exit\n", 2);
			print_error(MS_BASH, MS_EXIT, NULL, ERR_TOO_MANY_ARG);
			g_exit_code = 1;
			return ;
		}
		exit_with_argument(data, arg->content_exp_wq, cmd);
	}
	if (!is_in_pipeline(cmd))
		ft_putstr_fd("exit\n", 2);
	free_data(data);
	exit(EXIT_SUCCESS);
}
