#include <signal.h>
#include <unistd.h>

int	ft_puts(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (write(fd, s, i) + write(fd, "\n", 1));
}

int	ft_putnbr_fd(int n, int fd)
{
	const int	b = 10;
	const char	d[] = "0123456789";
	int			e;
	int			r;

	e = 1;
	r = write(fd, "-", (n < 0));
	n *= (n < 0) * 2 - 1;
	while (e <= -(n / b))
		e *= b;
	while (0 < e)
	{
		r += write(fd, &d[-(n / e % b)], 1);
		e /= b;
	}
	return (r + write(fd, "\n", 1));
}

void	sig(int sn)
{
	static char	c;
	static int	i;

	c = c | ((sn == SIGUSR1) << i);
	if (++i >= 8)
	{
		if (c == 0)
		{
			c = '\x6';
		}
		write(1, &c, 1);
		i = 0;
		c = 0;
	}
}

int	main(int ac, char **av)
{
	if (ac > 1 && av && ft_puts("usage: ./server (with no args)", 2))
		return (0);
	write(1, "pid: ", 5) && ft_putnbr_fd(getpid(), 1);
	if ((signal(SIGUSR1, sig) == SIG_ERR || signal(SIGUSR2, sig) == SIG_ERR)
		&& write(2, "Error\n", 6))
		return (1);
	while (1)
		pause();
	return (0);
}
