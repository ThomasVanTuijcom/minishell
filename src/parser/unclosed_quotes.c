/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:18:30 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/08/11 13:06:13 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_unclosed_quote_type(char *str)
{
	int	i;
	int	status_quote;

	i = 0;
	status_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			if (status_quote == 0)
				status_quote = 1;
			else if (status_quote == 1)
				status_quote = 0;
		}
		if (str[i] == '"')
		{
			if (status_quote == 0)
				status_quote = 2;
			else if (status_quote == 2)
				status_quote = 0;
		}
		i++;
	}
	return (status_quote);
}

int	check_for_unclosed_quotes(char *str)
{
	int flag;

	flag = get_unclosed_quote_type(str);
	if (flag > 0)
	{
		if (flag == 1)
			print_syntax_error(ERR_UNCLOSED, "\'");
		else if (flag == 2)
			print_syntax_error(ERR_UNCLOSED, "\"");
		g_exit_code = 2;
		return (1);
	}
	return (0);
}
