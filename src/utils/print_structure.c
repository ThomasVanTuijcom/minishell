/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_structure.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praucq <praucq@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:31:56 by praucq            #+#    #+#             */
/*   Updated: 2025/07/29 17:51:08 by praucq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
	{
		ft_putstr_fd(arr[i], 1);
		ft_putstr_fd(" ", 1);
	}
}

void	print_parser(t_data *data)
{
	t_p_node	*runner;

	if (!data || !data->parser)
		return ;
	runner = data->parser->head;
	while (runner)
	{
		ft_putstr_fd("cmds		= ", 1);
		print_array(runner->cmds);
		ft_putstr_fd("\ncontent		= ", 1);
		ft_putstr_fd(runner->content, 1);
		ft_putstr_fd("\ncontent_exp	= ", 1);
		ft_putstr_fd(runner->content_exp, 1);
		ft_putstr_fd("\ncontent_exp_wq	= ", 1);
		ft_putstr_fd(runner->content_exp_wq, 1);
		ft_putstr_fd("\n\n", 1);
		runner = runner->next;
	}
}
