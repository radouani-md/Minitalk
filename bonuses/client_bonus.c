/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 07:01:19 by mradouan          #+#    #+#             */
/*   Updated: 2025/03/09 16:01:39 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

pid_t	g_server_pid;

long	md_atoi(const char *str)
{
	int		i;
	int		sign;
	long	t;

	i = 0;
	sign = 1;
	t = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		t = t * 10 + (str[i] - 48);
		if (t > 2147483648)
			return (-1);
		i++;
	}
	return (t * sign);
}

void	treat_back(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (sig == SIGUSR1 && info->si_pid == g_server_pid)
		write(1, "All Is Done\n", 12);
}

void	send_char(pid_t g_server_pid, unsigned char c)
{
	int	i;
	int	bit;

	i = 0;
	while (i < 8)
	{
		bit = c % 2;
		if (bit == 1)
		{
			if (kill(g_server_pid, SIGUSR1) == -1)
				return (write(2, "Error\nKill prb", 14), exit(1));
		}
		else
		{
			if (kill(g_server_pid, SIGUSR2) == -1)
				return (write(2, "Error\nKill prb", 14), exit(1));
		}
		c = c / 2;
		usleep(200);
		usleep(200);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int					i;
	struct sigaction	sa;
	char				*msg;

	if (argc != 3)
		return (write(2, "Syntax: ./client <server_pid> <message>\n", 40), 1);
	g_server_pid = md_atoi(argv[1]);
	if (g_server_pid <= 0)
		return (write(2, "Error\nPID prb\n", 14), 1);
	sa.sa_flags = SA_SIGINFO;
	sa.__sigaction_u.__sa_sigaction = treat_back;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (write(2, "Error\nSEGACTION", 15), 1);
	i = 0;
	msg = argv[2];
	while (msg[i])
	{
		send_char(g_server_pid, msg[i]);
		i++;
	}
	send_char(g_server_pid, '\0');
}
