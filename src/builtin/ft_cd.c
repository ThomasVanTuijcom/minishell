/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:15:30 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/07 21:02:22 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cd_error(t_p_node *node, int error_type, bool *error)
{
	*error = true;
	if (error_type == CD_ERR_INVALID_OPTION)
	{
		print_option_invalid(node, MS_CD);
	}
	else if (error_type == CD_ERR_TOO_MANY_ARGS)
	{
		print_error(MS_BASH, MS_CD, NULL, ERR_TOO_MANY_ARG);
		g_exit_code = 1;
	}
}

int	count_simple_args(t_p_node *node)
{
	int			count;
	t_p_node	*curr;

	count = 0;
	curr = node->next;
	while (curr && curr->token_type != PIPE)
	{
		if (curr->token_type == SIMPLE_ARG)
			count++;
		curr = curr->next;
	}
	return (count);
}

void	handle_cd_target(t_data *data, t_p_node *node, char *oldpwd,
		bool *error)
{
	char	*arg;

	arg = node->content_exp_wq;
	if (!arg)
		arg = "";
	if (!node || node->token_type == OPTION || !arg || !*arg || !ft_strcmp(arg,
			"~"))
		cd_home(data, data->env, oldpwd, error);
	else if (!ft_strcmp(arg, "-"))
		cd_to_oldpwd(data, data->env, oldpwd, error);
	else if (!oldpwd && (!ft_strcmp(arg, ".") || !ft_strcmp(arg, "..")))
		print_err_lost_dir(oldpwd, arg, error);
	else if (arg[0] == '~' && arg[1] == '/')
		cd_to_home_append(data, oldpwd, error, node->content_exp_wq);
	else
		change_directory(data, oldpwd, arg, error);
}

bool	process_cd_argument(t_data *data, t_p_node *node, char *oldpwd,
		bool *error)
{
	int	nb_args;

	nb_args = count_simple_args(node->prev);
	*error = false;
	if (node->token_type == OPTION)
	{
		handle_cd_error(node, CD_ERR_INVALID_OPTION, error);
		return (false);
	}
	if (node->token_type == SIMPLE_ARG)
	{
		if (nb_args > 1)
		{
			handle_cd_error(node, CD_ERR_TOO_MANY_ARGS, error);
			return (false);
		}
		handle_cd_target(data, node, oldpwd, error);
	}
	if (!*error)
		g_exit_code = 0;
	return (true);
}

void	ft_cd(t_data *args, t_env_list *env, t_p_node *node)
{
	t_p_node	*curr;
	char		*oldpwd;
	bool		executed;
	int			nb_args;
	bool		error;

	error = false;
	oldpwd = NULL;
	curr = node->next;
	if (find_env_node_by_var(args->exp, "PWD"))
		oldpwd = ft_strdup(find_env_node_by_var(args->exp, "PWD")->content);
	executed = false;
	nb_args = count_simple_args(node);
	while (curr && curr->token_type != PIPE)
	{
		if (!process_cd_argument(args, curr, oldpwd, &error))
		{
			free(oldpwd);
			return ;
		}
		executed = true;
		curr = curr->next;
	}
	if (!executed && nb_args == 0)
		cd_home(args, env, oldpwd, &error);
}
