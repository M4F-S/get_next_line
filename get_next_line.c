/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfathy <mfathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:32:03 by mfathy            #+#    #+#             */
/*   Updated: 2025/12/16 15:21:45 by mfathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_resources(char **buffer, char *read_buf)
{
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	if (read_buf)
		free(read_buf);
	return (NULL);
}

static char	*extract_line(char **buffer)
{
	char	*line;
	char	*temp;
	size_t	len;

	if (!*buffer || !**buffer)
		return (free_resources(buffer, NULL));
	len = 0;
	while ((*buffer)[len] && (*buffer)[len] != '\n')
		len++;
	if ((*buffer)[len] == '\n')
	{
		line = ft_substr(*buffer, 0, len + 1);
		temp = ft_substr(*buffer, len + 1, ft_strlen(*buffer) - len - 1);
		free(*buffer);
		*buffer = temp;
		if (!line || !temp)
			return (free_resources(&line, NULL));
		return (line);
	}
	line = ft_substr(*buffer, 0, len);
	free_resources(buffer, NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*read_buf;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_buf)
		return (NULL);
	bytes_read = 1;
	while (!(buffer && ft_strchr(buffer, '\n')) && bytes_read > 0)
	{
		bytes_read = read(fd, read_buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_resources(&buffer, read_buf));
		read_buf[bytes_read] = '\0';
		if (bytes_read > 0)
			buffer = ft_strjoin_free(buffer, read_buf);
	}
	free(read_buf);
	if (!buffer)
		return (NULL);
	return (extract_line(&buffer));
}
