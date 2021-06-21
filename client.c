#include "minitalk.h"

int	g_flag = 0;

int	ft_sendnbr(pid_t pid, int *n, int sz)
{
	int			i;
	const int	nb = 8 * sizeof(int);

	i = 0;
	while (i / nb < sz)
	{
		kill(pid, (int []){SIGUSR2, SIGUSR1, 0}[n[i / nb] >> (i % nb) & 1]);
		i++;
		usleep(42);
	}
	return (0);
}

int	ft_sendstr(pid_t pid, char *s)
{
	int	i;

	i = 0;
	while (s[i / 8])
	{
		kill(pid, (int []){SIGUSR2, SIGUSR1, 0}[s[i / 8] >> (i % 8) & 1]);
		(void)(i % 8 == 0 && write(1, &s[i / 8], 1));
		i++;
		usleep(42);
	}
	return (0);
}

void	sig(int sn)
{
	if (g_flag != 1 && g_flag != 2 && sn == SIGUSR1)
		(void)(write(2, "ack: ", 5) && ft_putnbr_fd(g_flag, 2));
	else if (g_flag != 1 && g_flag != 2 && sn == SIGUSR2)
		(void)(write(2, "SIGUSR2 <- ", 11) && ft_putnbr_fd(g_flag, 2));
	if (sn == SIGUSR1)
		g_flag = 1;
	else if (sn == SIGUSR2)
		exit(0);
}

int	main(int ac, char **av)
{
	pid_t	pid;
	int		j;

	if (ac < 3 && ft_puts("usage: ./client {server-PID} {messages}", 2))
		return (0);
	if (((ft_atoi_p(av[1], &pid) || pid <= 0 || kill(pid, 0))
			&& ft_puts("Error: incorrect PID", 2))
		|| ((signal(SIGUSR1, sig) == SIG_ERR || signal(SIGUSR2, sig) == SIG_ERR)
			&& ft_puts("Error: SIG_ERR", 2)))
		return (1);
	(void)(write(2, "pid: ", 5) && ft_putnbr_fd(getpid(), 2));
	g_flag = pid;
	ft_sendnbr(pid, (int []){getpid()}, 1);
	usleep(420);
	j = 1;
	while (++j < ac)
	{
		ft_sendstr(pid, av[j]);
		(void)(j < ac - 1 && !ft_sendstr(pid, " "));
	}
	ft_sendnbr(pid, (int []){EOT << 24}, 1);
	usleep(420);
	return (0);
}
