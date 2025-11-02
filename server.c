/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harici <harici@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 08:07:19 by harici            #+#    #+#             */
/*   Updated: 2025/11/02 17:48:50 by harici           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static pid_t			pid = 0;
	static char				c = 0;
	static int				bit = 0;

	(void)context;
	if (pid == 0)
		pid = info->si_pid;
	if (pid != info->si_pid || (sig != SIGUSR1 && sig != SIGUSR2))
		return ;
	if (sig == SIGUSR2)
		c |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		if (c == '\n')
		{
			write(1, "\n", 1);
			pid = 0;
		}
		else
			write(1, &c, 1);
		bit = 0;
		c = 0;
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
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(2, "Error: Failed to set signal handler\n", 37);
		return (1);
	}
	while (1)
		pause();
	return (0);
}
