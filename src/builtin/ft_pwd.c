/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:31:06 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/06 20:57:07 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd_in_env_list(t_env_list *list, const char *new_pwd)
{
	t_env_node	*node;
	char		*joined_line;
	char		*content_trimmed;

	if (!list || !new_pwd)
		return ;
	node = list->head;
	while (node)
	{
		if (node->var_type == 1)
		{
			free(node->content);
			node->content = ft_strdup(new_pwd);
			free(node->trimmed);
			content_trimmed = ft_strtrim(node->content, " ");
			node->trimmed = trim_interior_spaces(content_trimmed);
			free(node->line);
			joined_line = ft_strjoin("PWD=", new_pwd);
			node->line = joined_line;
			node->value_set = 1;
			return ;
		}
		node = node->next;
	}
}

void	change_pwd_env(char *new_pwd, t_env_list *env)
{
	t_env_node	*pwd;

	pwd = find_env_node_by_var(env, "PWD");
	if (pwd)
		pwd->var_type = PWD;
	if (pwd && new_pwd)
		pwd->value_set = 1;
	else if (pwd)
		pwd->value_set = 0;
	update_pwd_in_env_list(env, new_pwd);
}

void	change_pwd_export(char *new_pwd, t_env_list *export)
{
	t_env_node	*pwd;

	pwd = find_env_node_by_var(export, "PWD");
	if (pwd)
		pwd->var_type = PWD;
	if (pwd && new_pwd)
		pwd->value_set = 1;
	else if (pwd)
		pwd->value_set = 0;
	update_pwd_in_env_list(export, new_pwd);
}

void	ft_pwd(t_p_node *node, t_data *data)
{
	t_p_node	*curr;
	char		*pwd;

	curr = node;
	while (curr)
	{
		if (curr->token_type == OPTION)
		{
			print_option_invalid(curr, MS_PWD);
			return ;
		}
		curr = curr->next;
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		print_error_lost_dir(NULL);
		return ;
	}
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	change_pwd_env(pwd, data->env);
	change_pwd_export(pwd, data->exp);
	g_exit_code = 0;
	free(pwd);
}
