/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remake_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:08:35 by praucq            #+#    #+#             */
/*   Updated: 2025/07/30 23:41:36 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_and_replace(char *ori, char *append)
{
	char	*ret;
	int		i;
	int		j;

	if (!ori && !append)
		return (NULL);
	if (!ori)
		return (ft_strdup(append));
	if (!append)
	{
		ret = ft_strdup(ori);
		return (free(ori), ret);
	}
	ret = ft_calloc(ft_strlen(ori) + ft_strlen(append) + 1, sizeof(char));
	if (!ret)
		return (free(ori), NULL);
	i = -1;
	j = -1;
	while (ori[++i])
		ret[i] = ori[i];
	while (append[++j])
		ret[i + j] = append[j];
	ret [i + j] = '\0';
	return (free(ori), ret);
}

static char	**env_lst_to_arr(t_data *data)
{
	t_env_node	*runner;
	char		**envp;
	int			i;

	if (!data || !data->env)
		return (NULL);
	if (data->envp)
		free_2d_array(data->envp);
	envp = (char **)ft_calloc((data->env->length + 1), sizeof(char *));
	if (!envp)
		return (NULL);
	runner = data->env->head;
	i = -1;
	while (runner && ++i < data->env->length)
	{
		envp[i] = ft_strdup(runner->var);
		if (envp[i] && runner->content)
			envp[i] = ft_strjoin_and_replace(envp[i], "=");
		if (envp[i] && runner->content)
			envp[i] = ft_strjoin_and_replace(envp[i], runner->content);
		if (!envp[i])
			return (free_2d_array(envp), NULL);
		runner = runner->next;
	}
	return (envp);
}

void	remake_envp(t_data *data)
{
	if (!data || !data->expired_envp)
		return ;
	data->envp = env_lst_to_arr(data);
	if (!data->envp)
	{
		g_exit_code = 12;
		return ;
	}
	data->expired_envp = 0;
}
