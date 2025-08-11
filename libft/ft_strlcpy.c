/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 08:59:23 by tvan-tui          #+#    #+#             */
/*   Updated: 2024/10/15 11:23:36 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_length;

	src_length = 0;
	while (src[src_length])
		src_length++;
	i = 0;
	while (dstsize != 0 && src[i] && i < dstsize - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dest[i] = '\0';
	return (src_length);
}
