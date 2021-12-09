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
		alpha[(int)*str]++;
//		if (alpha[(int)*str] == 0)
//			alpha[(int)*str] = 1;
		str++;
	}
}

void	ft_put_if_dup(int *alpha1, const int *alpha2, char *str)
{
	while (*str)
	{
		if (alpha1[(int)*str] == 1 && alpha2[(int)*str] == 1)
		{
			alpha1[(int)*str] = 0;
			write(1, &*str, 1);
		}
		str++;
	}
}

int	main(int argc, char *argv[0])
{
	int	alpha1[N];
	int	alpha2[N];

	if (argc == 3)
	{
		ft_alpha_init(alpha1);
		ft_alpha_init(alpha2);
		ft_histogram(alpha1, argv[1]);
		ft_histogram(alpha2, argv[2]);
		ft_put_if_dup(alpha1, alpha2, argv[1]);
	}
	ft_putendl();
	return (0);
}
