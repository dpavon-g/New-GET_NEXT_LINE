#include "libft/libft.h"

#include <fcntl.h>
/*

    Este programa usa funciones de mi libft, para que funcione sin ellas simplemente,
    hay que implementarlas y meterlas en una librería.
    Por otro lado el BUFFER_SIZE hay que pasarselo a la hora de complicar mediante
    la flag "-D BUFFER_SIZE=X".

*/
BUFFER_SIZE = 2;
void separate(char **str, char **line)
{
    char *aux;
    int i;
    char *ptr;

    while ((*str)[i] != '\n')
        i++;
    (*line) = malloc((i + 2) * sizeof(char));
    i = 0;
    while ((*str)[i] != '\n')
    {
        (*line)[i] = (*str)[i];
        i++;
    }
    (*line)[i] = '\n';
    (*line)[i+1] = '\0';
    ptr = ft_strchr((*str), '\n');
    ptr++;
    aux = ft_strdup(ptr);
    free((*str));
    (*str) = ft_strdup(aux);
    free(aux);
    aux = NULL;
}

char *get_next_line(int fd)
{
    static char *str;
    int         value;
    char        buff[BUFFER_SIZE + 1];
    char        *aux;
    char        *line;
    int         i;

    i = 0;
    value = read(fd, buff, BUFFER_SIZE);
    if (value < 0)
        return (NULL);
    if (value == 0 && !str)
        return (NULL);
    buff[value] = '\0';
    if (!str)
        str = ft_strdup(buff);
    else
    {
        aux = str;
        str = ft_strjoin(str, buff);
        free(aux);
    }
    while (value != 0 && ft_strchr(str, '\n') == 0)
    {
        aux = ft_strdup(str);
        free(str);
        str = NULL;
        value = read(fd, buff, BUFFER_SIZE);
        buff[value] = '\0';
        if (value != 0)
            str = ft_strjoin(aux, buff);
        else if (value == 0)
            str = ft_strdup(aux);
        free(aux);
    }
    if (value != 0)
        separate(&str, &line);
    else
    {
        if (ft_strchr(str, '\n'))
            separate(&str, &line);
        else
        {
            line = ft_strdup(str);
            free(str);
            str = NULL;
        }
    }
    return(line);
}