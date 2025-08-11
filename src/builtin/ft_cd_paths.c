/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:57:18 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/07 21:02:48 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_directory(t_data *args, char *oldpwd, char *path, bool *error)
{
	int		ret;
	char	*pwd;

	ret = chdir(path);
	pwd = getcwd(NULL, 0);
	if (ret < 0)
	{
		print_error(MS_BASH, MS_CD, path, ERR_NO_FOD);
		g_exit_code = 1;
		*error = true;
	}
	else
	{
		update_env(pwd, oldpwd, args);
		g_exit_code = 0;
	}
	free(pwd);
	free(oldpwd);
}

void	cd_to_oldpwd(t_data *args, t_env_list *env, char *oldpwd, bool *error)
{
	char		*oldpwd_value;
	t_env_node	*node;

	node = find_env_node_by_var(env, "OLDPWD");
	if (node)
		oldpwd_value = node->content;
	else
		oldpwd_value = NULL;
	if (!oldpwd_value || ft_strcmp(oldpwd_value, "") == 0)
	{
		print_error(MS_BASH, MS_CD, NULL, ERR_OLDPWD_NULL);
		free(oldpwd);
		g_exit_code = 1;
		*error = true;
		return ;
	}
	ft_putstr_fd(oldpwd_value, 1);
	ft_putstr_fd("\n", 1);
	change_directory(args, oldpwd, oldpwd_value, error);
}

void	cd_home(t_data *args, t_env_list *env, char *oldpwd, bool *error)
{
	char		*home;
	t_env_node	*node;

	node = find_env_node_by_var(env, "HOME");
	if (node)
		home = node->content;
	else
		home = NULL;
	if (!home)
	{
		print_error(MS_BASH, MS_CD, NULL, ERR_HOME);
		free(oldpwd);
		g_exit_code = 1;
		*error = true;
		return ;
	}
	if (!home[0])
	{
		free(oldpwd);
		return ;
	}
	change_directory(args, oldpwd, home, error);
}

void	cd_to_home_append(t_data *data, char *oldpwd, bool *error, char *arg)
{
	char		*new_arg;
	t_env_node	*node;

	node = find_env_node_by_var(data->env, "HOME");
	if (node)
		new_arg = ft_strdup(node->content);
	else
		new_arg = NULL;
	if (!new_arg || ft_strcmp(new_arg, "") == 0)
	{
		print_error(MS_BASH, MS_CD, NULL, ERR_HOME);
		free(oldpwd);
		g_exit_code = 1;
		*error = true;
		return ;
	}
	else
		new_arg = ft_strjoin_and_replace(new_arg, &arg[1]);
	change_directory(data, oldpwd, new_arg, error);
	free(new_arg);
}
