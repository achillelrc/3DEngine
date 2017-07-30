/*
** gnl.c for gnl in /home/binary/All/Wolf3D/Wolf/MY
** 
** Made by Laroche Achille
** Login   <binary@epitech.net>
** 
** Started on  Sun Jun 11 19:29:24 2017 Laroche Achille
** Last update Mon Jun 12 20:12:59 2017 Laroche Achille
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"

char	*realloc_and_add(char *str, char add_char)
{
  int	i;
  char	*ret;

  i = 0;
  if (add_char == 10)
    add_char = 0;
  while (str[i])
    i++;
  if (!(ret = malloc(sizeof(char) * (i + 2))))
    {
      free(str);
      return (NULL);
    }
  i = 0;
  while (str[i])
    {
      ret[i] = str[i];
      i++;
    }
  ret[i++] = add_char;
  ret[i] = 0;
  free(str);
  return (ret);
}

char	*get_next_line(const int fd)
{
  char	*rturned;
  char	c;

  c = 0;
  if (!(rturned = malloc(sizeof(char) * 1)))
    return (NULL);
  rturned[0] = 0;
  while (c != '\n')
    {
      if (read(fd, &c, 1) < 0)
	{
	  free(rturned);
	  return (NULL);
	}
      if (fd != 0 && c == 0)
	return (NULL);
      if (!(rturned = realloc_and_add(rturned, c)))
	return (NULL);
    }
  return (rturned);
}

int	**check_map(int **map, int x, int y)
{
  int	i;
  int	j;

  i = 1;
  j = 0;
  while (map[i - 1][j] >= 0 && map[i - 1][j] <= 5 && j < x - 1)
    {
      if (map[i - 1][j] != 1)
	return (NULL);
      j++;
    }
  while (map[i] != NULL)
    {
      j = 0;
      if (map[i][0] != 1)
	return (NULL);
      while (map[i][j] >= 0 && map[i][j] <= 5 && j < x - 1)
	j++;
      if (map[i][j] != 1)
	return (NULL);
      i++;
    }
  return (map);
}

int	**convfile(char **file, int x, int y)
{
  int	i;
  int	j;
  int	**map;

  if (!(map = malloc(sizeof(int*) * (y + 1))))
    return (NULL);
  i = 0;
  while (i < y)
    {
      if (!(map[i] = malloc(sizeof(int) * x)))
	return (NULL);
      j = 0;
      while (j < x)
	{
	  if (file[i][j] < '0' || file[i][j] > '9')
	    return (NULL);
	  map[i][j] = file[i][j] - 48;
	  j++;
	}
      i++;
    }
  map[i] = NULL;
  return (check_map(map, x, y));
}

int	**get_file(int fd, int *x, int *y)
{
  char	**file;
  int	i;

  i = 2;
  if (!(file = malloc(sizeof(char*) * i)))
    return (NULL);
  while ((file[i++ - 2] = get_next_line(fd)) != NULL)
    file = realloc(file, i * sizeof(char*));
  file[i - 3] = NULL;
  *y = i - 3;
  if (file[0] == NULL || file[1] == NULL)
    return (NULL);
  i = 0;
  while (file[1][i])
    i++;
  *x = i;
  return (convfile(file, *x, *y));
}
