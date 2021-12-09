#include <stdarg.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;

	va_start(ap, format);
	while (*format)
	{
		if (*format != '%')
			ft_putchar(*format);
		else
		{
			if (*(++format) == 's')
				ft_putstr(va_arg(ap, char *));
			else if (*format == 'd')
				return (1);
			else if (*format == 'x')
				return (0);
		}
		format++;
	}
	va_end(ap);
	return (0);
}

int main(void)
{
	ft_printf("Test %s", "String");
	return (0);
}
