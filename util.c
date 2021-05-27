#include "minitalk.h"

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
