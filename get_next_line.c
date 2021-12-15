/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 10:57:12 by lmasson           #+#    #+#             */
/*   Updated: 2021/01/27 17:33:13 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		check_backslash_n(int *next_call_line, char *buffer, int *len)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			if ((i + 1) != BUFFER_SIZE)
				*next_call_line = i + 1;
			else
				*next_call_line = 0;
			*len = i;
			return (1);
		}
		i++;
	}
	*len = i;
	*next_call_line = 0;
	return (0);
}

int		ft_strlen(char *tab)
{
	int j;

	j = 0;
	while (tab[j])
		j++;
	return (j);
}

char	*ft_strncpy(char *line, const char *buffer, int len)
{
	int			i;

	i = 0;
	if (line || buffer)
	{
		while (i < len)		
		{
			*(line + i) = *(buffer + i);
			i++;
		}
	}
	line[i] = '\0';
	return (line);
}

char	*ft_strncat(char *dest, char *src, size_t nb)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dest);
	j = 0;
	while (src[j] && j < nb)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*transfer(char **line, char *buffer, int len)
{
	int		previous_malloc;
	char	*temp;

	if (*line == NULL)
	{
		temp = malloc(sizeof(char) * (len + 1));
		ft_strncpy(temp, buffer, len);
	}
	else
	{
		previous_malloc = ft_strlen(*line);
		temp = malloc(sizeof(char) * (len + previous_malloc + 1));
		ft_strncpy(temp, *line, previous_malloc);
		free(*line);
		ft_strncat(temp, buffer, len);
	}
	return (temp);
}

int	manage_line(char **line, char *buffer, int *next_call_line, int fd)
{
	int len;

	len = 0;
	if (check_backslash_n(next_call_line, buffer, &len) == 1)
		{
			*line = transfer(line, buffer, len);
			return (1);
		}
		else
		{
			*line = transfer(line, buffer, len);
			get_next_line(fd, line);
		}
	return (-1);
}


int		get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1]= "";
	static int	next_call_line = 0;
	int			read_return;
	int			ret;
	
	read_return = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	*line = NULL;
	if (next_call_line != 0)
		manage_line(line, &buffer[next_call_line], &next_call_line, fd);
	while (0 < read_return)
	{
		read_return = read(fd, buffer, BUFFER_SIZE);
		buffer[read_return] = '\0';
		ret = manage_line(line, buffer, &next_call_line, fd);
		if (ret == 1)
			return (1);
		if (ret == -1)
			return (-1);
		/*if (check_backslash_n(&next_call_line, buffer, &len) == 1)
		{
			*line = transfer(line, buffer, len);
			return (1);
		}
		else
		{
			*line = transfer(line, buffer, len);
			get_next_line(fd, line);
		}*/
	}
	return (0); 
}
