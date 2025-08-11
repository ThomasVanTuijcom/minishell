/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:56:44 by tvan-tui          #+#    #+#             */
/*   Updated: 2025/07/24 17:43:43 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_quoted_word(char *str, char quote, int *count, int *i)
{
	(*count)++;
	(*i)++;
	while (str[(*i)] != quote)
		(*i)++;
	(*i)++;
}

/*
	peut etre devoir fusionner avec une autre fonction cf
	count_quoted_word ou ajouter args->quote_parse si utile
*/
int	length_word_quotes(char *str, char quote)
{
	int	length;

	length = 1;
	str++;
	while (*str && *str != quote)
	{
		length++;
		str++;
	}
	length++;
	str++;
	return (length);
}
