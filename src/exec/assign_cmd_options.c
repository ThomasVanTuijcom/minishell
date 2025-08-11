/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_cmd_options.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:11:19 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/29 11:29:35 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd_nodes(t_p_list *list)
{
	t_p_node	*curr;
	int			count;

	curr = list->head;
	count = 0;
	while (curr)
	{
		if (curr->token_type == CMD)
			count++;
		curr = curr->next;
	}
	return (count);
}

int	fill_cmd_args_array(t_p_node *node, char **argv, int start_index, int limit)
{
	int	i;

	i = start_index;
	while (node && i < limit)
	{
		if (node->token_type == OPTION || node->token_type == SIMPLE_ARG)
		{
			argv[i] = ft_strdup(node->content_exp_wq);
			if (!argv[i])
			{
				free_2d_array_n(argv, i);
				return (0);
			}
			i++;
		}
		node = node->next;
	}
	argv[i] = NULL;
	return (1);
}

char	**build_cmd_args_array(t_p_node *cmd_node, int arg_count)
{
	char		**argv;
	t_p_node	*node;

	node = cmd_node->next;
	argv = malloc(sizeof(char *) * (arg_count + 1));
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(cmd_node->content_exp_wq);
	if (!argv[0])
		return (free(argv), NULL);
	if (!fill_cmd_args_array(node, argv, 1, arg_count))
		return (NULL);
	return (argv);
}

int	assign_args_to_cmds(t_p_list *list, int *arg_counts)
{
	t_p_node	*node;
	int			index;

	node = list->head;
	index = 0;
	while (node)
	{
		if (node->token_type == CMD)
		{
			node->cmds = build_cmd_args_array(node, arg_counts[index]);
			if (!node->cmds)
				return (0);
			index++;
		}
		node = node->next;
	}
	return (1);
}

int	assign_cmd_options(t_p_list *list)
{
	int			cmd_count;
	int			*arg_counts;

	cmd_count = count_cmd_nodes(list);
	if (cmd_count <= 0)
		return (-1);
	arg_counts = build_cmd_args_counts(list, cmd_count);
	if (!arg_counts)
		return (-1);
	if (!assign_args_to_cmds(list, arg_counts))
	{
		free(arg_counts);
		return (-1);
	}
	free(arg_counts);
	return (0);
}
