/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:18:30 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/14 12:44:10 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	unclosed_f[0] : for '
	unclosed_f[1] : for "
*/
void	get_unclosed_quote_type(char *str, bool unclosed_f[2])
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			if (!unclosed_f[0])
				unclosed_f[0] = true;
			else
				unclosed_f[0] = false;
		}
		if (str[i] == '"')
		{
			if (!unclosed_f[1])
				unclosed_f[1] = true;
			else
				unclosed_f[1] = false;
		}
		i++;
	}
}

int	check_for_unclosed_quotes(char *str)
{
	bool	unclosed_f[2];

	unclosed_f[0] = false;
	unclosed_f[1] = false;
	get_unclosed_quote_type(str, unclosed_f);
	if (unclosed_f[0] || unclosed_f[1])
	{
		if (unclosed_f[0])
			print_syntax_error(ERR_UNCLOSED, "'");
		else if (unclosed_f[1])
			print_syntax_error(ERR_UNCLOSED, "\"");
		g_exit_code = 2;
		return (1);
	}
	return (0);
}
