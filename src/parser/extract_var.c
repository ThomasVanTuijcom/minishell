/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:47:03 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/06 15:41:37 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	calc_var_length(int *count, int *i, char *str)
{
	if (str[*i + 1] == '$' || str[*i + 1] == '\0' || is_quote(str[*i + 1])
		|| (!ft_isalnum(str[*i + 1]) && str[*i + 1] != '_'))
	{
		(*count)++;
		if (str[*i + 1] != '\0')
		{
			if (is_quote(str[*i + 2]))
				(*count)++;
		}
		return ;
	}
	(*i)++;
	if (ft_isdigit(str[*i]) || str[*i] == '?')
	{
		(*count)++;
		return ;
	}
	while (ft_isalnum(str[*i]) || str[*i] == '_')
	{
		(*i)++;
		(*count)++;
	}
}

int	get_var_length(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			calc_var_length(&count, &i, str);
			break ;
		}
		else
			i++;
	}
	return (count);
}

static void	is_there_a_var(char **str)
{
	if (*(*str + 1) == '?')
		(*str)++;
	else if (*(*str + 1) != '$' && ft_strcmp("$", *str) && !is_quote(*(*str
				+ 1)) && ((ft_isalnum(*(*str + 1)) == 1) || *(*str
				+ 1) == '_'))
		(*str)++;
	else if (is_quote(*(*str + 1)) && is_quote(*(*str + 2)))
		(*str)++;
}

char	*extract_variable_name(char **str)
{
	char	*var;
	int		len;

	if (!str || !*str || **str != '$')
		return (NULL);
	if (**str == '\0')
		return (NULL);
	len = get_var_length(*str);
	if (len == 0)
		return (NULL);
	is_there_a_var(str);
	var = ft_substr(*str, 0, len);
	*str += len;
	return (var);
}
