/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmasson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:09:32 by lmasson           #+#    #+#             */
/*   Updated: 2021/01/27 10:56:45 by lmasson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int		main(void)
{
	int		fd;
	char	*line = NULL;
	int		ret;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		printf("Erreur d'ouverture du fd %s\n", strerror(errno));
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("%s\n", line);
		free(line);
	}
	if (ret == -1)
		printf("Erreur de lecture de gnl\n");
	close(fd);
	return (0);
}
