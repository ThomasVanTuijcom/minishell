/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvan-tui <tvan-tui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:19:32 by tvan-tui          #+#    #+#             */
/*   Updated: 2024/10/17 11:20:51 by tvan-tui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_num_length(int n)
{
	int	length;

	length = 1;
	if (n < 0)
	{
		n = -n;
		length++;
	}
	while (n / 10 > 0)
	{
		length++;
		n /= 10;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = get_num_length(n);
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	result = (char *) malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len > 0)
	{
		result[--len] = n % 10 + '0';
		n /= 10;
	}
	if (sign)
		result[0] = '-';
	return (result);
}
