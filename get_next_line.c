/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celadia <celadia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:05:52 by celadia           #+#    #+#             */
/*   Updated: 2021/12/07 17:05:52 by celadia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

void	*ft_free_ptr(void *ptr)
{
	free(ptr);
	return (NULL);
}

void	ft_str_cpy(char *str, ssize_t line_len)
{
	char		*shift;

	shift = str + line_len;
	while (*shift)
		*(str++) = *(shift++);
	*str = '\0';
}

int	ft_str_chr(char *str, ssize_t *len)
{
	*len = 0;
	while (*str && *str != '\n' && ++*len)
		str++;
	if (*str == '\n' && ++*len)
		return (1);
	return (0);
}

char	*ft_str_join(char *dst, char *src, ssize_t line_len)
{
	char	*temp_join;
	char	*temp_dst;
	char	*join;

	if (*src == '\0')
		return (dst);
	line_len++;
	join = malloc(sizeof(char) * (line_len));
	if (!join)
		return (NULL);
	temp_join = join;
	temp_dst = dst;
	while (*dst && --line_len)
		*(join++) = *(dst++);
	while (*src && --line_len)
		*(join++) = *(src++);
	*join = '\0';
	free(temp_dst);
	return (temp_join);
}

char	*get_read_file(int fd, char *stat_str)
{
	char		*line_str;
	ssize_t		line_len;
	ssize_t		stat_len;
	ssize_t		full_len;

	line_str = malloc(sizeof(char) * 1);
	*line_str = '\0';
	full_len = 0;
	if (!ft_str_chr(stat_str, &line_len))
	{
		stat_len = 1;
		while (stat_len > 0 && !ft_str_chr(stat_str, &line_len))
		{
			full_len += line_len;
			line_str = ft_str_join(line_str, stat_str, full_len);
			stat_len = read(fd, stat_str, BUFFER_SIZE);
			if (!line_str || stat_len == -1)
				return (NULL);
			*(stat_str + stat_len) = '\0';
		}
	}
	line_str = ft_str_join(line_str, stat_str, full_len + line_len);
	ft_str_cpy(stat_str, line_len);
	return (line_str);
}

char	*get_next_line(int fd)
{
	static char		*stat_str;
	char			*line_str;
	char			check;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, &check, 0) == -1)
		return (NULL);
	if (!stat_str)
	{
		stat_str = malloc(sizeof(char) * ((ssize_t)BUFFER_SIZE + 1));
		if (!stat_str)
			return (NULL);
		*stat_str = '\0';
	}
	line_str = get_read_file(fd, stat_str);
	if (line_str == NULL || *line_str == '\0')
	{
		stat_str = ft_free_ptr(stat_str);
		line_str = ft_free_ptr(line_str);
	}

	char c = getchar();
	(void) c;

	return (line_str);
}
