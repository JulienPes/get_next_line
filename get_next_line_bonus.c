/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpes <jpes@student.42nice.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:34:32 by jpes              #+#    #+#             */
/*   Updated: 2023/06/12 10:48:37 by jpes             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_and_get(int fd, char *buffer, char *stash)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		if (bytes_read == -1)
			return (0);
		if (bytes_read == 0)
			break ;
		if (!stash)
			stash = ft_strdup("");
		temp = stash;
		stash = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (stash);
}

char	*ft_put_right_place(char *line)
{
	char	*stash;
	size_t	n;

	n = 0;
	while (line[n] != '\n' && line[n] != '\0')
		n ++;
	if (line[n] == '\0' || line[0] == '\0')
		return (0);
	stash = ft_substr(line, n + 1, ft_strlen(line) - n);
	if (stash[0] == '\0')
	{
		free(stash);
		stash = NULL;
	}
	line[n + 1] = '\0';
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (read(fd, 0, 0) < 0)
	{
		free (stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	line = ft_read_and_get(fd, buffer, stash[fd]);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	stash[fd] = ft_put_right_place(line);
	return (line);
}
