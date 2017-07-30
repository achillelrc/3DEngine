/*
** working.c for wolf3d in /home/binary/All/Wolf3D/Wolf/MY/wolf3d
** 
** Made by Laroche Achille
** Login   <binary@epitech.net>
** 
** Started on  Mon Jun 12 12:04:12 2017 Laroche Achille
** Last update Mon Jun 12 19:52:17 2017 Laroche Achille
*/

#include "my.h"

sfColor		choose_color(t_ray *ray)
{
  sfColor	color;
  int		pos;

  pos = Map[ray->pos_i[0]][ray->pos_i[1]];
  if (pos == 1)
    color = sfCyan;
  else if (pos == 2)
    color = sfMagenta;
  else if (pos == 3)
    color = sfBlue;
  else if (pos == 4)
    color = sfBlack;
  else if (pos == 0)
    color = sfGreen;
  if (ray->is_side == 1)
    {
      color.r /= 1.5;
      color.g /= 1.5;
      color.b /= 1.5;
    }
  return (color);
}

int		wolf(t_data *data, t_rend *render)
{
  t_ray		*ray;
  sfUint8*	pixels;
  sfEvent	event;

  pixels = create_pixel_buffer(WIDTH, HEIGHT);
  sfRenderWindow_clear(render->win, sfWhite);
  data->x = 0;
  while ((ray = fill_ray(data, data->x)) != NULL && data->x++ < WIDTH)
    draw_ray(ray, render, pixels);
  if (ray == NULL)
    return (-1);
  while (sfRenderWindow_pollEvent(render->win, &event))
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
      sfRenderWindow_close(render->win);
  if (sfKeyboard_isKeyPressed(sfKeyLeft) == sfTrue)
    rot_cam(data, 1);
  else if (sfKeyboard_isKeyPressed(sfKeyRight) == sfTrue)
    rot_cam(data, -1);
  else if (sfKeyboard_isKeyPressed(sfKeyUp) == sfTrue)
    mov_cam(data, 1);
  else if (sfKeyboard_isKeyPressed(sfKeyDown) == sfTrue)
    mov_cam(data, -1);
  sfRenderWindow_clear(render->win, sfWhite);
  sfRenderWindow_drawSprite(render->win, render->sprite, NULL);
  sfRenderWindow_display(render->win);
}

int		main(int ac, char **av)
{
  int		start[2];
  int		fd;
  t_rend	*render;
  t_data	*data;

  if (ac < 2)
    return (84);
  else
    if ((fd = open(av[1], 0444)) == -1)
      return (84);
  if ((Map = get_file(fd, &start[0], &start[1])) == NULL)
    return (84);
  if ((start[0] < 5 || start[1] < 5) ||
      (render = init_render()) == NULL ||
      (data = init_data(start)) == NULL)
    return (84);
  while (sfRenderWindow_isOpen(render->win))
    if (wolf(data, render) == -1)
      return (84);
  sfRenderWindow_destroy(render->win);
  return (0);
}
