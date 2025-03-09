/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 06:56:14 by mradouan          #+#    #+#             */
/*   Updated: 2025/03/09 15:09:59 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_server
{
	int	pid;
	int	current_char;
	int	number_byte;
	int	index_posi;
}	t_server;

int		power_of_two(int exp);
long	md_atoi(const char *str);
char	*md_itoa(int n);
size_t	md_strlen(char const *s);
void	ft_putstr(char *str);

#endif