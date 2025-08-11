/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 08:53:39 by tvan-tui          #+#    #+#             */
/*   Updated: 2024/10/10 09:47:42 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (dest[i])
		i++;
	while (src[j])
		j++;
	if (dstsize <= i)
		return (dstsize + j);
	j = 0;
	while (src[j])
	{
		if (k < dstsize - i - 1)
		{
			dest[i + k] = src[j];
			k++;
		}
		j++;
	}
	dest[i + k] = '\0';
	return (i + j);
}
