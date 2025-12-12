#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int     main(void)
{
    int fd = open("txt",O_RDONLY);
    char *line;
    int i=0;

    line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
        i++;
    }
    printf("%s", line);
    free(line);
    close (fd);
}