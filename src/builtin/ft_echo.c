/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:34:37 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/07 15:08:51 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_echo_option(const char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

t_p_node	*skip_n_options(t_p_node *node, int *suppress_newline)
{
	while (node && node->token_type == OPTION && node->token_type != PIPE)
	{
		if (is_valid_echo_option(node->content_exp_wq))
		{
			*suppress_newline = 1;
			node = node->next;
		}
		else
			break ;
	}
	return (node);
}

void	print_argument(const char *arg, int *first, const char *arg_with_quotes)
{
	if (!arg_with_quotes[0])
		return ;
	if (!*first)
		write(STDOUT_FILENO, " ", 1);
	write(STDOUT_FILENO, arg, ft_strlen(arg));
	*first = 0;
}

void	ft_echo(t_p_node *parser)
{
	t_p_node	*node;
	int			suppress_newline;
	int			is_first_arg;

	node = parser->next;
	suppress_newline = 0;
	is_first_arg = 1;
	node = skip_n_options(node, &suppress_newline);
	while (node && node->token_type != PIPE)
	{
		if (node->token_type == SIMPLE_ARG || node->token_type == OPTION)
		{
			print_argument(node->content_exp_wq, &is_first_arg,
				node->content_exp);
		}
		node = node->next;
	}
	if (!suppress_newline)
		write(STDOUT_FILENO, "\n", 1);
	g_exit_code = 0;
}
