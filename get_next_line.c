/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfathy <mfathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:45:03 by mfathy            #+#    #+#             */
/*   Updated: 2025/12/09 16:17:47 by mfathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*extract_line(char **buffer)
{
	char	*line;
	char	*newline_pos;
	char	*temp;

	if (!*buffer || !**buffer)
		return (NULL);
	newline_pos = ft_strchr(*buffer, '\n');
	line = ft_substr(*buffer, 0, newline_pos - *buffer + 1);
	if (!line)
		return (NULL);
	if (newline_pos)
	{
		temp = ft_substr(newline_pos + 1, 0, ft_strlen(newline_pos + 1));
		if (!temp)
			return (free_and_return(&line, buffer, NULL));
		free(*buffer);
		*buffer = temp;
		return (line);
	}
	else
		return (free_and_return(buffer, NULL, line));
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		read_buf[BUFFER_SIZE + 1];
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, read_buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_and_return(&buffer, NULL, NULL));
		read_buf[bytes_read] = '\0';
		if (bytes_read > 0)
			buffer = ft_strjoin_free(buffer, read_buf);
		if (!buffer)
			return (NULL);
	}
	write(1, "Extract line\n", 13);
	return (extract_line(&buffer));
}
