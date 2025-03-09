/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:28:52 by mradouan          #+#    #+#             */
/*   Updated: 2025/03/09 15:11:25 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	power_of_two(int exp)
{
	int		result;

	result = 1;
	while (exp--)
		result *= 2;
	return (result);
}

static int	get_length(int n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*md_itoa(int n)
{
	char	*result;
	int		len;
	long	num;

	num = n;
	len = get_length(n);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (num < 0)
	{
		result[0] = '-';
		num = -num;
	}
	while (len-- > 0)
	{
		if (result[len] == '-')
			break ;
		result[len] = (num % 10) + '0';
		num /= 10;
	}
	return (result);
}

size_t	md_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
