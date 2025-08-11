/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:44:48 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/06 21:42:02 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_oldpwd_in_env_list(t_env_list *list, const char *new_pwd)
{
	t_env_node	*node;
	char		*joined_line;
	char		*content_trimmed;

	if (!list || !new_pwd)
		return ;
	node = list->head;
	while (node)
	{
		if (node->var_type == 2)
		{
			free(node->content);
			node->content = ft_strdup(new_pwd);
			free(node->trimmed);
			content_trimmed = ft_strtrim(node->content, " ");
			node->trimmed = trim_interior_spaces(content_trimmed);
			free(node->line);
			joined_line = ft_strjoin("OLDPWD=", new_pwd);
			node->line = joined_line;
			return ;
		}
		node = node->next;
	}
}

void	change_oldpwd_env(char *new_pwd, t_env_list *env)
{
	t_env_node	*pwd;
	t_env_node	*oldpwd;

	pwd = find_env_node_by_var(env, "PWD");
	oldpwd = find_env_node_by_var(env, "OLDPWD");
	if (oldpwd)
		oldpwd->var_type = OLDPWD;
	if (oldpwd && pwd && new_pwd)
		oldpwd->value_set = 1;
	else if (oldpwd)
		oldpwd->value_set = 0;
	if (new_pwd && oldpwd && pwd)
		update_oldpwd_in_env_list(env, new_pwd);
	else if (oldpwd)
	{
		free(oldpwd->content);
		free(oldpwd->line);
		free(oldpwd->trimmed);
		oldpwd->content = ft_strdup("");
		oldpwd->trimmed = ft_strdup("OLDPWD");
		oldpwd->line = ft_strdup("");
		oldpwd->value_set = 0;
	}
}

void	change_oldpwd_export(char *new_pwd, t_env_list *export)
{
	t_env_node	*pwd;
	t_env_node	*oldpwd;

	pwd = find_env_node_by_var(export, "PWD");
	oldpwd = find_env_node_by_var(export, "OLDPWD");
	if (oldpwd)
		oldpwd->var_type = OLDPWD;
	if (oldpwd && pwd && new_pwd)
		oldpwd->value_set = 1;
	else if (oldpwd)
		oldpwd->value_set = 0;
	if (new_pwd && oldpwd && pwd)
		update_oldpwd_in_env_list(export, new_pwd);
	else if (oldpwd)
	{
		free(oldpwd->content);
		free(oldpwd->line);
		free(oldpwd->trimmed);
		oldpwd->content = ft_strdup("");
		oldpwd->trimmed = ft_strdup("OLDPWD");
		oldpwd->line = ft_strdup("");
		oldpwd->value_set = 0;
	}
}

void	update_env(char *pwd, char *oldpwd, t_data *data)
{
	t_env_node	*env_pwd;
	t_env_node	*exp_pwd;
	t_env_node	*env_oldpwd;

	exp_pwd = find_env_node_by_var(data->exp, "PWD");
	if (exp_pwd)
	{
		env_pwd = find_env_node_by_var(data->env, "PWD");
		if (!env_pwd)
			export_var_to_env(data, data->env, "PWD=", 1);
		change_pwd_env(pwd, data->env);
		change_pwd_export(pwd, data->exp);
	}
	env_oldpwd = find_env_node_by_var(data->env, "OLDPWD");
	if (env_oldpwd)
	{
		change_oldpwd_env(oldpwd, data->env);
		change_oldpwd_export(oldpwd, data->exp);
	}
	g_exit_code = 0;
}
