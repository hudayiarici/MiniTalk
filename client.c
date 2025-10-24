/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harici <harici@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 08:30:54 by harici            #+#    #+#             */
/*   Updated: 2025/10/24 21:00:34 by harici           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	g_received = 0;

static void	ack_handler(int sig)
{
	(void)sig;
	g_received = 1;
}

static int	wait_for_ack(void)
{
	int	timeout;

	timeout = 0;
	while (!g_received && timeout++ < 100)
		usleep(10);
	return (timeout >= 100);
}

static int	send_char(int server_pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		g_received = 0;
		if (c & (1 << bit))
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		if (wait_for_ack())
			return (-1);
		bit++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int					server_pid;
	int					i;
	struct sigaction	sa;

	if (argc != 3)
		return (write(2, "Usage: ./client [PID] [message]\n", 33), 1);
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		return (write(2, "Error: Invalid PID\n", 20), 1);
	sa.sa_handler = ack_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (write(2, "Error: Failed to set signal handler\n", 37), 1);
	i = 0;
	while (argv[2][i])
	{
		if (send_char(server_pid, argv[2][i]) == -1)
			return (write(2, "Error: Failed to send signal\n", 30), 1);
		i++;
	}
	send_char(server_pid, '\n');
	write(1, "Message sent successfully!\n", 27);
	return (0);
}
