/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewaltz <ewaltz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:31:09 by ewaltz            #+#    #+#             */
/*   Updated: 2025/12/11 11:34:34 by ewaltz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

  #include <fcntl.h>
  #include <stdio.h>

  int main(int argc, char **argv)
  {
      int   fd;
      char *line;

      if (argc != 2)
      {
          printf("Usage: %s <fichier>\n", argv[0]);
          return (1);
      }

      fd = open(argv[1], O_RDONLY);
      if (fd < 0)
      {
          perror("open");
          return (1);
      }

      while ((line = get_next_line(fd)) != NULL)
      {
          printf("--\"%s\"\n", line);
          free(line);
      }

      close(fd);
      return (0);
  }
 
