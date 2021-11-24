/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:08:05 by gvarys            #+#    #+#             */
/*   Updated: 2021/11/23 13:59:32 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	kills(pid_t pid, int sigusr)
{			
	if (kill(pid, sigusr))
	{
		write(1, "Signal error\n", 13);
		exit(0);
	}
}

static void	ft_print_pid(void)
{
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
}

static void	ft_signals(int signal, siginfo_t *sigingo, void *context)
{
	static int				i = 0;
	static unsigned char	c = 0;

	(void)context;
	c |= (signal == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			kills(sigingo->si_pid, SIGUSR2);
			return ;
		}
		ft_putchar_fd(c, 1);
		c = 0;
		kills(sigingo->si_pid, SIGUSR1);
	}
	else
		c <<= 1;
}

int	main(void)
{
	struct sigaction	s_signals;

	ft_print_pid();
	s_signals.sa_flags = SA_SIGINFO;
	s_signals.sa_sigaction = ft_signals;
	if ((sigaction(SIGUSR1, &s_signals, 0) == -1))
	{
		ft_putstr_fd("Sigaction falils\n", 1);
		exit(0);
	}
	if ((sigaction(SIGUSR2, &s_signals, 0) == -1))
	{
		ft_putstr_fd("Sigaction falils\n", 1);
		exit(0);
	}
	while (1)
		pause();
	return (0);
}
