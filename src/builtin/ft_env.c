/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praucq <praucq@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:12:45 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/30 13:58:27 by praucq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_env(t_env_node *node)
{
	t_env_node	*curr;

	curr = node;
	while (curr)
	{
		if (ft_strcmp(curr->line, "\0"))
		{
			if (curr->value_set)
				ft_putstr_fd(curr->line, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		curr = curr->next;
	}
}

void	ft_env(t_p_node *node, t_env_list *list)
{
	t_p_node	*curr;

	if (!list)
		return ;
	curr = node;
	while (curr && curr->token_type != PIPE)
	{
		if (curr->token_type == OPTION)
		{
			print_option_invalid(curr, MS_ENV);
			return ;
		}
		curr = curr->next;
	}
	display_env(list->head);
	g_exit_code = 0;
}
