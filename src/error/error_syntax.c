/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:04:38 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/06 16:31:19 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error(char *msg, char *syntax)
{
	ft_putstr_fd(msg, 0);
	ft_putstr_fd(syntax, 0);
	ft_putstr_fd("'\n", 0);
}

int	print_syntax_error_meta(char *sign)
{
	print_syntax_error(ERR_TOKEN, sign);
	g_exit_code = 2;
	return (-1);
}

int	syntax_error_meta(t_p_list *list)
{
	t_p_node	*curr;

	curr = list->head;
	if (!curr)
		return (-1);
	if (curr->token_type == PIPE || curr->token_type == WRONG_META)
		return (print_syntax_error_meta(curr->content_exp_wq));
	while (curr && curr->next)
	{
		if (curr->token_type == WRONG_META)
			return (print_syntax_error_meta(curr->content_exp_wq));
		else if (is_metachar_type(curr->token_type)
			&& is_metachar_type(curr->next->token_type))
			return (print_syntax_error_meta(curr->next->content_exp_wq));
		curr = curr->next;
	}
	if (is_metachar_type(curr->token_type))
		return (print_syntax_error_meta(curr->content_exp_wq));
	return (1);
}
