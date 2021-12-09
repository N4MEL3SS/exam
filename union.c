#include <unistd.h>

#define N 256

void	ft_putendl(void)
{
	write(1, "\n", 1);
}

void	ft_alpha_init(int *alpha)
{
	int	i;

	i = -1;
	while (++i < N)
		alpha[i] = 0;
}

void	ft_histogram(int *alpha, char *str)
{
	while (*str)
	{
		if (alpha[(int)*str] == 0)
			alpha[(int)*str] = 1;
		str++;
	}
}

void	ft_put_wo_dup(int *alpha, char *str)
{
	while (*str)
	{
		if (alpha[(int)*str] == 1)
		{
			alpha[(int) *str] = 0;
			write(1, &*str, 1);
		}
		str++;
	}
}

int	main(int argc, char *argv[0])
{
	int	alpha[N];

	if (argc == 3)
	{
		ft_alpha_init(alpha);
		ft_histogram(alpha, argv[1]);
		ft_histogram(alpha, argv[2]);
		ft_put_wo_dup(alpha, argv[1]);
		ft_put_wo_dup(alpha, argv[2]);
	}
	ft_putendl();
	return (0);
}
