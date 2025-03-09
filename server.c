/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 07:00:51 by mradouan          #+#    #+#             */
/*   Updated: 2025/03/09 15:09:41 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_bit_index;

int	num_bytes(int first_byte)
{
	if (first_byte < 128)
		return (1);
	else if (first_byte >= 192 && first_byte < 224)
		return (2);
	else if (first_byte >= 224 && first_byte < 240)
		return (3);
	else if (first_byte >= 240 && first_byte < 248)
		return (4);
	return (1);
}

void	reset_on_new_pid(siginfo_t *info, t_server *srv)
{
	if (srv->pid == 0)
		srv->pid = info->si_pid;
	if (info->si_pid != srv->pid)
	{
		g_bit_index = 0;
		srv->current_char = 0;
		srv->number_byte = 1;
		srv->index_posi = 0;
		srv->pid = info->si_pid;
	}
}

void	print_reset(char *msg, int *index_posi, int *number_byte)
{
	write(1, msg, *number_byte);
	*index_posi = 0;
	*number_byte = 1;
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static char			msg[4];
	static t_server		srv = {0, 0, 1, 0};

	(void)context;
	reset_on_new_pid(info, &srv);
	if (sig == SIGUSR1)
		srv.current_char += power_of_two(g_bit_index);
	g_bit_index++;
	if (g_bit_index == 8)
	{
		msg[srv.index_posi++] = srv.current_char;
		if (srv.index_posi == 1)
			srv.number_byte = num_bytes(srv.current_char);
		if (srv.index_posi == srv.number_byte)
			print_reset(msg, &srv.index_posi, &srv.number_byte);
		srv.current_char = 0;
		g_bit_index = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	char				*pid_ser;

	pid_ser = md_itoa(getpid());
	write(1, "PID Of the Server : ", 20);
	ft_putstr(pid_ser);
	write(1, "\n", 1);
	sa.sa_flags = SA_SIGINFO;
	sa.__sigaction_u.__sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (write(2, "Error\nSEGACTION", 15), 1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (write(2, "Error\nSEGACTION", 15), 1);
	while (1)
		pause();
}
