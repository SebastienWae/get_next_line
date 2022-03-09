/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swaegene <swaegene@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:46:45 by swaegene          #+#    #+#             */
/*   Updated: 2022/03/06 15:14:27 by swaegene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_first_line(char **line_buf)
{
	char	*line;
	char	*tmp_buf;
	char	*end_ptr;

	end_ptr = ft_strchr(*line_buf, (int) '\n');
	if (end_ptr)
	{
		line = ft_substr(*line_buf, 0, (end_ptr - *line_buf) + 1);
		tmp_buf = ft_strdup(end_ptr + 1);
		free(*line_buf);
		*line_buf = tmp_buf;
	}
	else
	{
		line = ft_strdup(*line_buf);
		free(*line_buf);
		*line_buf = 0;
	}
	return (line);
}

void	read_file(int fd, char **line_buf)
{
	int		b;
	char	buf[BUFFER_SIZE + 1];
	char	*line;

	b = 1;
	while (b && !ft_strchr(*line_buf, (int) '\n'))
	{
		b = read(fd, buf, BUFFER_SIZE);
		if (b < 0)
			break ;
		buf[b] = 0;
		line = ft_strjoin(*line_buf, (char *)buf);
		free(*line_buf);
		*line_buf = line;
	}
}

char	*get_next_line(int fd)
{
	static char	*line_buf[10240];

	if (fd >= 0)
	{
		if (!(line_buf[fd]))
		{
			line_buf[fd] = malloc(sizeof(char));
			*(line_buf[fd]) = 0;
		}
		read_file(fd, &(line_buf[fd]));
		if (!*(line_buf[fd]))
		{
			free(line_buf[fd]);
			line_buf[fd] = 0;
			return (NULL);
		}
		return (get_first_line(&(line_buf[fd])));
	}
	return (NULL);
}
