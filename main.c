/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfathy <mfathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:10:00 by mfathy            #+#    #+#             */
/*   Updated: 2025/12/09 16:12:05 by mfathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;
	int		line_count;

	printf("=== Testing get_next_line ===\n\n");
	fd = open("test3.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	line_count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		line_count++;
		printf("Line %d: %s", line_count, line);
		free(line);
	}
	close(fd);
	printf("\n=== Total lines read: %d ===\n", line_count);
	return (0);
}
