/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:25:08 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/13 21:53:01 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	try_free(char *s)
{
	if (s)
		free(s);
}

t_p_node	*skip_faulty_nodes(t_p_node *curr)
{
	size_t	runner;
	int		contain_var;

	while (curr && curr->token_type != PIPE)
	{
		runner = -1;
		contain_var = 0;
		while (curr->content[++runner])
		{
			if (curr->content[runner] == '$' && curr->content[runner + 1]
				&& curr->content[runner + 1] != '\'' && curr->content[runner
					+ 1] != '"')
				contain_var = 1;
		}
		if (contain_var && !curr->content_exp_wq[0])
			curr = curr->next;
		else
			return (curr);
	}
	return (curr);
}

bool	is_minishell(char *path)
{
	size_t	i;

	if (!ft_strcmp(path, "./minishell"))
		return (true);
	i = ft_strlen(path);
	if (i < 11)
		return (false);
	i -= 10;
	if (!ft_strcmp(&path[i], "/minishell"))
		return (true);
	return (false);
}
