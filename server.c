/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harici <harici@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 08:07:19 by harici            #+#    #+#             */
/*   Updated: 2025/10/24 21:37:12 by harici           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_client	g_client = {0, 0, 0};

static void	signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (g_client.pid == 0)
		g_client.pid = info->si_pid;
	if (g_client.pid != info->si_pid)
		return ;
	if (sig == SIGUSR2)
		g_client.c |= (1 << g_client.bit);
	g_client.bit++;
	if (g_client.bit == 8)
	{
		if (g_client.c == '\n')
		{
			write(1, "\n", 1);
			g_client.pid = 0;
		}
		else
			write(1, &g_client.c, 1);
		g_client.bit = 0;
		g_client.c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd((int)getpid(), 1);
	ft_putstr_fd("\n", 1);
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		||sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(2, "Error: Failed to set signal handler\n", 37);
		return (1);
	}
	while (1)
		pause();
	return (0);
}
