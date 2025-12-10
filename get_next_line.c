/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewaltz <ewaltz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:15:18 by ewaltz            #+#    #+#             */
/*   Updated: 2025/12/10 11:58:18 by ewaltz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char *str);

int	get_index(char *str)
{
  int	i;

  i = 0;
  if (!str)
	return (-1);
  while (str[i])
  {
	if (str[i] == '\n')
	  return (i);
	i++;
  }
  return (-1);
}

char	*ft_strdup(char *str, int len)
{
  int	i;
  char	*new_str;

  i = 0;
  if (!str || len > ft_strlen(str) || len < 0)
	return (NULL);
  new_str = malloc(sizeof(char) * (len + 1));
  if (!new_str)
	return (NULL);
  while (i < len)
  {
	new_str[i] = str[i];
	i++;
  }
  new_str[i] = '\0';
  return (new_str);
}

int	ft_strlen(char *str)
{
  int	i;

  i = 0;
  if (!str)
	return (0);
  while (str[i])
	i++;
  return (i);
}

char	*get_rest(char *str, int start)
{
  int	len;
  int	i;
  char	*new_str;

  i = 0;
  if (!str)
	return (NULL);
  len = ft_strlen(str);
  if (start >= len)
	return (NULL);
  new_str = malloc(sizeof(char) * (len - start + 1));
  if (!new_str)
	return (NULL);
  while (str[start])
	new_str[i++] = str[start++];
  new_str[i] = '\0';
  return (new_str);
}


char	*str_join(char *rest, char *buffer)
{
  int	y;
  int	i;
  char	*new_rest;

  i = 0;
  y = 0;
  new_rest = malloc(sizeof(char) * (ft_strlen(rest) + ft_strlen(buffer) + 1));
  if (!new_rest)
	return (NULL);
  if (rest)
  {
	while (rest[i])
	{
	  new_rest[i] = rest[i];
	  i++;
	}
  }
  while (buffer[y])
	new_rest[i++] = buffer[y++];
  new_rest[i] = '\0';
  free (rest);
  return (new_rest);
}


char	*get_next_line(int fd)
{
  static char	*rest;
  char			buffer[BUFFER_SIZE + 1];
  char			*ligne;
  int			bytes;
  int 			index;

  if (fd < 0 || BUFFER_SIZE <= 0)
	return (NULL);
  while (get_index(rest) == -1)
  {
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes < 0)
	{
	  free (rest);
	  return (NULL);
	}
	if (bytes == 0)
	  break;
	if (bytes > 0)
	{
	  buffer[bytes] = '\0';
	  rest = str_join(rest, buffer);
	}
  }
  index = get_index(rest) + 1;
  ligne = ft_strdup(rest, index);
  rest = get_rest(rest, index);
  return (ligne);
}
//
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include "get_next_line.h"
//
// int main(int argc, char **argv)
// {
//     int   fd;
//     char *line;
//
//     if (argc != 2)
//     {
//         printf("Usage: %s <fichier>\n", argv[0]);
//         return (1);
//     }
//
//     fd = open(argv[1], O_RDONLY);
//     if (fd < 0)
//     {
//         perror("open");
//         return (1);
//     }
//
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("LIGNE => \"%s\"\n", line);
//         free(line);
//     }
//
//     close(fd);
//     return (0);
// }
