#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int power_of_2(int exp)
{
	int result;

	result = 1;
	while (exp--)
		result *= 2;
	return (result);
}

void send_char(pid_t server_pid, char c)
{
	int	i;
	int	bit;
	i = 0;
	while (i < 8)
	{
		bit = c % 2;
		if (bit == 1)
		{
			if (kill(server_pid, SIGUSR1) == -1)
				return (write(2, "Error\nKill prb", 14), exit(1));
		}
		else
		{
			if (kill(server_pid, SIGUSR2) == -1)
				return (write(2, "Error\nKill prb", 14), exit(1));
		}
		c = c / 2;
		usleep(200);
		i++;
	}
}

int main(int argc, char **argv)
{
	int i;
	pid_t server_pid;

	i = 0;
	if (argc != 3)
	{
		write(1, "Usage: ./client <server_pid> <message>\n", 41);
		return (1);
	}
	if (argv[2] < 0)
		return (write(2, "Error\n PID prb", 14), 1);
	server_pid = atoi(argv[1]);
	while (argv[2][i])
	{
		send_char(server_pid, argv[2][i]);
		i++;
	}
	return (0);
}
