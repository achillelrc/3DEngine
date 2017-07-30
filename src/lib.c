/*
** scan.c for scanner in /home/binary/All/Wolf3D/Wolf/MY/wolf3d
** 
** Made by Laroche Achille
** Login   <binary@epitech.net>
** 
** Started on  Mon Jun 12 15:18:38 2017 Laroche Achille
** Last update Tue Jun 13 22:40:35 2017 Laroche Achille
*/

#include "my.h"

void		my_put_pixel(sfUint8* pixels, int x, int y, sfColor color)
{
  pixels[(WIDTH * y + x) * 4] = color.r;
  pixels[(WIDTH * y + x) * 4 + 1] = color.g;
  pixels[(WIDTH * y + x) * 4 + 2] = color.b;
  pixels[(WIDTH * y + x) * 4 + 3] = color.a;
}

void draw_square(sfUint8* pixels, int x, int y, sfColor color)
{
  int xx;
  int yy;
  
  xx = x + 2;
  yy = y + 2;
  while (y < yy)
    {
      x = xx - 2;
      while (x < xx)
	{
	  my_put_pixel(pixels, x, y, color);
	  x++;
	}
      y++;
    }
}

void		my_draw_line(sfUint8* pixels, sfVector2i fr, sfVector2i to, sfColor color)
{
  int		m;
  float		t;
  int		x;
  int		y;
  static int u;

  x = 0;
  m = sqrt(pow(to.x - fr.x, 2) + pow(to.y - fr.y, 2));
  u++;
  if (u < 10) fprintf(stderr, "%d\n", m);
  t = 0;
  while (t < 1)
    {
      x = ((1 - t) * fr.x + t * to.x);
      y = ((1 - t) * fr.y + t * to.y);
      draw_square(pixels, x, y, color);
      t += 1 / (double)m;
    }
}

sfUint8*	create_pixel_buffer(int width, int height)
{
  int		i;
  sfUint8*	pixels;

  if (!(pixels = malloc(width * height * 4 * sizeof(*pixels))))
    return (NULL);
  i = 0;
  while (i < width * height * 4)
    pixels[i++] = 0;
  return (pixels);
}

sfRenderWindow		*create_window(char *name, int width, int height)
{
  sfRenderWindow	*window;
  sfVideoMode		mode;

  mode.width = width;
  mode.height = height;
  mode.bitsPerPixel = 32;
  window = sfRenderWindow_create(mode, name, sfResize | sfClose, NULL);
  if (window == NULL)
    exit(EXIT_FAILURE);
  return (window);
}
