#include <signal.h>
#include <unistd.h>
#include <limits.h>

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

int	ft_atoi_p(char *s, int *n)
{
	int			m;
	const int	b = 10;

	*n = 0;
	while (('\t' <= *s && *s <= '\r') || *s == ' ')
		s++;
	m = (*s == '-');
	s += (*s == '+' || *s =='-');
	while (*s)
	{
		if (*s < '0' || '9' < *s || (*n > INT_MAX / b)
			|| (*n == INT_MAX / b && *s - '0' > INT_MAX % b + m))
			return (1);
		*n = *n * b + *s++ - '0';
	}
	*n *= 1 + (m * -2);
	return (0);
}

int	ft_sendstr(int pid, char *s)
{
	int	i;

	i = 0;
	while (i < 8 || s[i / 8])
	{
		kill(pid, (int []){SIGUSR2, SIGUSR1}[s[i / 8] >> (i % 8) & 1]);
		i++;
		usleep(42);
	}
	return (0);
}

int	main(int ac, char **av)
{
	int	pid;
	int	j;

	if (ac < 3 && ft_puts("usage: ./client server-PID message", 2))
		return (0);
	if ((ft_atoi_p(av[1], &pid) || pid <= 0 || kill(pid, 0)) && ft_puts("Error: incorrect PID", 2))
		return (1);
	j = 2;
	while (j < ac)
	{
		ft_sendstr(pid, av[j]);
		if (av[++j])
			ft_sendstr(pid, " ");
	}
	ft_sendstr(pid, "\n");
	ft_sendstr(pid, "");
	return (0);
}
