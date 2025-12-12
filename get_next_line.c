/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 get_next_line.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: ewaltz <ewaltz@student.42.fr>				+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/12/05 14:15:18 by ewaltz			   #+#	  #+#			  */
/*	 Updated: 2025/12/11 11:31:41 by ewaltz			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_buffer(char *rest, int bytes, char *buffer, int fd)
{
	while (get_index(rest) == -1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free (rest);
			rest = NULL;
			free (buffer);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		if (bytes > 0)
		{
			buffer[bytes] = '\0';
			rest = str_join(rest, buffer);
		}
	}
	free (buffer);
	return (rest);
}

char	*check_params(int fd)
{
	char	*buffer;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free (buffer);
		return (NULL);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char		*rest;
	char			*buffer;
	char			*ligne;
	int				bytes;
	int				index;

	bytes = 0;
	buffer = check_params(fd);
	if (!buffer)
		return (NULL);
	rest = read_buffer(rest, bytes, buffer, fd);
	if (get_index(rest) == -1)
	{
		index = ft_strlen(rest);
		ligne = ft_strdup(rest, index);
		rest = get_rest(rest, index);
	}
	else
	{
		index = get_index(rest) + 1;
		ligne = ft_strdup(rest, index);
		rest = get_rest(rest, index);
	}
	return (ligne);
}
