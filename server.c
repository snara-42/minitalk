#include "minitalk.h"

void	sig(int sn)
{
	static unsigned int	c;
	static int			i;
	static int			n;

	c = ((c & ~(1 << i)) | (sn == SIGUSR1) << i);
	if (++i % (8 * sizeof(int)) == 0 && n++ == 0)
	{
		if (write(2, "\nfrom: ", 7) && ft_putnbr_fd(c, 2)
			&& kill(c, SIGUSR1))
			ft_puts("Error: incorrect PID", 2);
		i = 0;
		c <<= 8;
	}
	else if (i % 8 == 0 && n > 0)
	{
		if (c == END)
			n = 0;
		else if (c & 0xff)
			write(1, &c, 1);
		i = 0;
		c <<= 8;
	}
}

int	main(int ac, char **av)
{
	if (ac > 1 && av && ft_puts("usage: ./server (with no args)", 2))
		return (0);
	if ((signal(SIGUSR1, sig) == SIG_ERR || signal(SIGUSR2, sig) == SIG_ERR)
		&& ft_puts("Error: SIG_ERR", 2))
		return (1);
	write(1, "pid: ", 5) && ft_putnbr_fd(getpid(), 1);
	while (1)
		pause();
	return (0);
}
