/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 07:00:51 by mradouan          #+#    #+#             */
/*   Updated: 2025/03/08 16:06:26 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int bit_index;

int num_bytes(int first_byte)
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

void reset_on_new_pid(siginfo_t *info, int *pid, int *current_char,
					  int *number_byte, int *index_posi)
{
	if (*pid == 0)
		*pid = info->si_pid;
	if (info->si_pid != *pid)
	{
		bit_index = 0;
		*current_char = 0;
		*number_byte = 1;
		*index_posi = 0;
		*pid = info->si_pid;
	}
}

void ft_help(char *msg, int *index_posi, int *number_byte)
{
	write(1, msg, *number_byte);
	*index_posi = 0;
	*number_byte = 1;
}

void handle_signal(int sig, siginfo_t *info, void *context)
{
	static char msg[4];
	static int current_char;
	static int pid;
	static int number_byte = 1;
	static int index_posi = 0;

	(void)context;
	reset_on_new_pid(info, &pid, &current_char, &number_byte, &index_posi);
	if (sig == SIGUSR1)
		current_char += power_of_two(bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		msg[index_posi++] = current_char;
		if (index_posi == 1)
			number_byte = num_bytes(current_char);
		if (index_posi == number_byte)
			ft_help(msg, &index_posi, &number_byte);
		if (current_char == '\0' && kill(pid, SIGUSR1) == -1)
			return (write(2, "Error\nKill prb", 14), exit(1));
		current_char = 0;
		bit_index = 0;
	}
}
int main()
{
	printf("PID Of the Server : %d\n", getpid());

	struct sigaction sa;

	sa.sa_flags = SA_SIGINFO;
	sa.__sigaction_u.__sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	while (1)
		pause();
	return (0);
}
