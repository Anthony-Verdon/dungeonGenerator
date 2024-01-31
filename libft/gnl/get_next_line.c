/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: averdon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:03:42 by averdon           #+#    #+#             */
/*   Updated: 2022/11/11 15:30:50 by averdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

static char	*empty_buffer(char *buffer, char *line)
{
	int				j;
	int				i;

	j = 0;
	i = 1;
	while (buffer[i - 1] != '\n' && buffer[i])
		i++;
	while (buffer[i] != '\0')
	{
		buffer[j] = buffer[i];
		i++;
		j++;
	}
	while (j < i)
	{
		buffer[j] = '\0';
		j++;
	}
	line = ft_strdup_gnl(buffer);
	if (!line)
		return (NULL);
	return (line);
}

static char	*fill_line(char *line, char *buffer)
{
	char	*temp;

	if (!line)
	{
		line = ft_strdup_gnl(buffer);
		if (!line)
			return (NULL);
	}
	else
	{
		temp = ft_strjoin_gnl(line, buffer);
		free(line);
		if (!temp)
			return (NULL);
		line = temp;
	}
	return (line);
}

static char	*check_value_read(int value_read, char *line)
{
	if ((line && value_read < 0) || (line && !line[0]))
	{
		free(line);
		line = NULL;
	}
	if (line && line[0])
		return (line);
	return (NULL);
}

static char	*complete_line(char *buffer, char *line, int fd, int i)
{
	int	value_read;

	value_read = read(fd, buffer, BUFFER_SIZE);
	if (value_read <= 0)
		return (check_value_read(value_read, line));
	buffer[value_read] = '\0';
	while (i < BUFFER_SIZE && buffer[i] && buffer[i] != '\n')
		i++;
	line = fill_line (line, buffer);
	if (!line)
		return (NULL);
	if (buffer[i] == '\n')
	{
		if (i + 1 == BUFFER_SIZE)
			buffer[0] = '\0';
		return (line);
	}
	return (complete_line(buffer, line, fd, 0));
}

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE + 1];
	int				i;
	char			*line;

	line = NULL;
	if (buffer[0] && BUFFER_SIZE != 1)
	{
		line = empty_buffer(buffer, line);
		if (!line)
			return (NULL);
		i = 0;
		while (line[i])
		{
			if (line[i] == '\n')
				return (line);
			i++;
		}
	}
	line = complete_line(buffer, line, fd, 0);
	return (line);
}
