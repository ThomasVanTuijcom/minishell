/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:17:47 by tvan-tui          #+#    #+#             */
/*   Updated: 2024/10/17 12:27:32 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	int		i;

	i = 0;
	if (start > ft_strlen(s))
	{
		result = (char *) malloc(1);
		if (!result)
			return (NULL);
	}
	else
	{
		if (ft_strlen(s) - start < len)
			len = ft_strlen(s) - start;
		result = (char *) malloc(sizeof(char) * (len + 1));
		if (!result)
			return (NULL);
		while (len)
		{
			result[i++] = s[start++];
			len--;
		}
	}
	result[i] = '\0';
	return (result);
}
