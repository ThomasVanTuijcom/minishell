/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praucq <praucq@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:26:47 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/29 21:09:40 by praucq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_node	*create_shlvl_node(char *lower_shlvl)
{
	t_env_node	*node;
	char		*tmp;
	int			lvl;
	char		*shlvl;

	tmp = ft_substr(lower_shlvl, 0, 6);
	if (!tmp)
		return (NULL);
	lvl = ft_atoi(&lower_shlvl[6]);
	shlvl = ft_itoa(++lvl);
	if (!shlvl)
		return (free(tmp), NULL);
	tmp = ft_strjoin_and_replace(tmp, shlvl);
	free(shlvl);
	if (!tmp)
		return (NULL);
	node = new_env_node(tmp);
	free(tmp);
	return (node);
}

void	create_env(t_data *data, char **envp)
{
	int			i;
	t_env_node	*node;

	i = 0;
	node = NULL;
	init_env_list(&data->exp);
	init_env_list(&data->env);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "SHLVL=", 6))
			node = create_shlvl_node(envp[i]);
		else
			node = new_env_node(envp[i]);
		if (!node)
		{
			free_env_list(data->env);
			data->env = NULL;
			return ;
		}
		env_list_addback(&data->env, node);
		i++;
	}
}
