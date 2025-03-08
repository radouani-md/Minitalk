/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradouan <mradouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 07:00:51 by mradouan          #+#    #+#             */
/*   Updated: 2025/03/06 07:06:40 by mradouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int power_of_two(int exp)
{
	int result;

	result = 1;
	while (exp--)
		result *= 2;
	return (result);
}

int bit_index;

void handle_signal(int sig, siginfo_t *info, void *context)
{
	static char message;
	static char current_char;
	static int	pid;

	(void)context;
	if (pid == 0)
	{
		pid = info->si_pid;
	}
	if (pid != 0 && info->si_pid != pid)
	{
		bit_index = 0;
		current_char = 0;
		pid = info->si_pid;
	}
	if (sig == SIGUSR1)
		current_char += power_of_two(bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		message = current_char;
		write(1, &message, 1);
		bit_index = 0;
		current_char = 0;
	}
}

int main()
{
	printf("PID Of the Server : %d\n", getpid());

	struct sigaction sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	while (1)
		pause();
	return 0;
}
