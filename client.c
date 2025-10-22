/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harici <harici@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 08:30:54 by harici            #+#    #+#             */
/*   Updated: 2025/10/22 17:16:18 by harici           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	send_char(int server_pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
		{
			if (kill(server_pid, SIGUSR2) == -1)
				return (-1);
		}
		else
		{
			if (kill(server_pid, SIGUSR1) == -1)
				return (-1);
		}
		usleep(500);
		bit++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	server_pid;
	int	i;

	if (argc != 3)
		return (write(2, "Usage: ./client [PID] [message]\n", 33), 1);
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		return (write(2, "Error: Invalid PID\n", 20), 1);
	i = 0;
	while (argv[2][i])
	{
		if (send_char(server_pid, argv[2][i]) == -1)
			return (write(2, "Error: Failed to send signal\n", 30), 1);
		i++;
	}
	send_char(server_pid, '\n');
	return (0);
}
