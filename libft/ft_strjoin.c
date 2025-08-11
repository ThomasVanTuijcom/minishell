/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:35:21 by tvan-tui          #+#    #+#             */
/*   Updated: 2024/10/15 12:54:56 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*result;
	size_t	s1_length;
	size_t	s2_length;

	i = 0;
	j = 0;
	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	result = (char *) malloc(sizeof(char) * (s1_length + s2_length + 1));
	if (!result)
		return (NULL);
	while (j < s1_length)
		result[i++] = s1[j++];
	j = 0;
	while (j < s2_length)
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}
