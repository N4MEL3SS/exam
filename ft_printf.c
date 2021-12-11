#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

typedef struct s_form
{
	int		width;
	int 	dot;
	int 	precis;
}				t_form;

int		ft_str_len(char *str)
{
	int	i;

	i = 0;
	while (*str && ++i)
		str++;
	return (i);
}

void	ft_putstr(char *str, t_form flag)
{
	int	len;

	len = ft_str_len(str);
	if (flag.dot == 1 && flag.precis < len)
		len = flag.precis;
	flag.width -= len;
	while (flag.width-- > 0)
		write(1, " ", 1);
	while (len-- > 0)
		write(1, str++, 1);
}

char	*ft_parse(char *str, int *n)
{
	while (48 <= *str && *str <= 57)
		*n = *n * 10 + (*(str++) - 48);
	return (str);
}

void	ft_put_digit(int n, t_form flag)
{
	int		n_range;
	int		n_len;
	int		sign;
	int		i;
	char	d[11];

	n_len = 0;
	sign = 0;
	n_range = 1;
	i = 0;
	if (n < 0 && ++n_len)
	{
		n_range = -1;
		sign = 1;
	}
	while (n / 10 / n_range && ++n_len)
		n_range *= 10;
	while (n_range)
	{
		d[i++] = (char)(n / n_range + 48);
		n %= n_range;
		n_range /= 10;
	}
	d[i] = '\0';
	if (n_len >= flag.precis)
		flag.precis = 0;
	if (n_len >= flag.width)
		flag.width = 0;
	if (flag.width >= flag.precis && flag.precis > n_len)
		flag.width -= (flag.precis + sign);
	else if (flag.precis > flag.width)
		flag.width = 0;
	else if (flag.width > n_len)
		flag.width -= (n_len + sign);
	if (flag.precis > n_len)
		flag.precis -= n_len;
	while (flag.width-- > 0)
		write(1, " ", 1);
	if (sign)
		write(1, "-", 1);
	while (flag.precis-- > 0)
		write(1, "0", 1);
	i = 0;
	while (d[i])
		write(1, &d[i++], 1);
}

void	ft_put_hex(int n, t_form flag)
{
	int		n_range;
	int		n_len;
	int		sign;
	int		i;
	char	d[11];
	int		temp;

	n_len = 0;
	sign = 0;
	n_range = 1;
	i = 0;
	if (n < 0)
	{
		n_range = -1;
		sign = 1;
	}
	while (n / 16 / n_range && ++n_len)
		n_range *= 16;
	while (n_range)
	{
		temp = n / n_range;
		if (temp > 10)
			d[i++] = (char)(temp + 87);
		else
			d[i++] = (char)(temp + 48);
		n %= n_range;
		n_range /= 16;
	}
	d[i] = '\0';
	if (n_len >= flag.precis)
		flag.precis = 0;
	if (n_len >= flag.width)
		flag.width = 0;
	if (flag.width >= flag.precis && flag.precis > n_len)
		flag.width -= flag.precis;
	else if (flag.precis > flag.width)
		flag.width = 0;
	else if (flag.width > n_len)
		flag.width -= n_len;
	if (flag.precis > n_len)
		flag.precis -= (n_len + 1);
	while (flag.width-- > 0)
		write(1, " ", 1);
	while (flag.precis-- > 0)
		write(1, "0", 1);
	i = 0;
	while (d[i])
		write(1, &d[i++], 1);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	t_form	flag;

	flag.width = 0;
	flag.dot = 0;
	flag.precis = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format != '%')
			write(1, &*format, 1);
		else
		{
			format = ft_parse((char *)++format, &flag.width);
			if (*format == '.')
			{
				flag.dot = 1;
				format = ft_parse((char *)++format, &flag.precis);
			}
			if (*(format) == 's')
				ft_putstr(va_arg(ap, char *), flag);
			else if (*format == 'd')
				ft_put_digit(va_arg(ap, int), flag);
			else if (*format == 'x')
				ft_put_hex(va_arg(ap, int), flag);
		}
		format++;
	}
	va_end(ap);
	return (0);
}

int main(void)
{
	ft_printf("%12.12x\n", INT32_MAX);
	printf("%12.12x\n", INT32_MAX);
	return (0);
}
