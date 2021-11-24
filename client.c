/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 10:08:22 by gvarys            #+#    #+#             */
/*   Updated: 2021/11/23 13:59:23 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	check_PID(char *str)
{
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			str++;
		else
			return (0);
	}
	return (1);
}

static void	kills(pid_t pid, int sigusr)
{			
	if (kill(pid, sigusr))
	{
		write(1, "Signal error\n", 13);
		exit(0);
	}
}

static void	ft_signals(int signal, siginfo_t *sigingo, void *context)
{
	(void)sigingo;
	(void)context;
	if (signal == SIGUSR1)
		ft_putstr_fd("Signal recieved!\n", 1);
}

static void	send_bit(pid_t pid, char *str)
{
	int				i;
	unsigned char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
				kills(pid, SIGUSR2);
			else
				kills(pid, SIGUSR1);
			usleep(50);
		}
	}
	i = 8;
	while (i--)
	{
		kills(pid, SIGUSR1);
		usleep(50);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	s_signals;

	if (argc == 3 && check_PID(argv[1]))
	{
		s_signals.sa_flags = SA_SIGINFO;
		s_signals.sa_sigaction = ft_signals;
		if (sigaction(SIGUSR1, &s_signals, 0))
		{
			ft_putstr_fd("Sigaction falils\n", 1);
			exit(0);
		}
		if (sigaction(SIGUSR2, &s_signals, 0))
		{
			ft_putstr_fd("Sigaction falils\n", 1);
			exit(0);
		}
		send_bit(ft_atoi(argv[1]), argv[2]);
	}
	else
		ft_putstr_fd("Please write PID and message next time", 1);
	return (0);
}
