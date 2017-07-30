/*
** init.c for  in /home/binary/All/Wolf3D/Wolf/MY/wolf3d
** 
** Made by Laroche Achille
** Login   <binary@epitech.net>
** 
** Started on  Mon Jun 12 15:27:40 2017 Laroche Achille
** Last update Mon Jun 12 15:27:48 2017 Laroche Achille
*/

#include "my.h"

t_rend		*init_render()
{
  t_rend	*render;

  render = NULL;
  if ((render = malloc(sizeof(*render))) == NULL)
    return (NULL);
  if ((render->win = create_window("Wolf3D", WIDTH, HEIGHT)) == NULL)
    return (NULL);
  render->sprite = sfSprite_create();
  render->texture = sfTexture_create(WIDTH, HEIGHT);
  sfRenderWindow_setFramerateLimit(render->win, 60);
  sfSprite_setTexture(render->sprite, render->texture, sfTrue);
  sfRenderWindow_clear(render->win, sfWhite);
  return (render);
}

t_data		*init_data(int *start)
{
  t_data	*data;

  data = NULL;
  if ((data = malloc(sizeof(*data))) == NULL)
    return (NULL);
  data->front_speed = 0.3;
  data->rot_speed = 0.3;
  data->x_dir = -1;
  data->y_dir = 0;
  data->x_cam = 0;
  data->y_cam = 0.66;
  data->x_pos = start[0] / 2;
  data->y_pos = start[1] / 2;
  return (data);
}

t_ray		*fill_ray(t_data *data, int x)
{
  t_ray		*ray;

  ray = NULL;
  if ((ray = malloc(sizeof(*ray))) == NULL)
    return (NULL);
  if ((ray->steps = malloc(sizeof(int) * 2)) == NULL ||
      (ray->sides = malloc(sizeof(double) * 2)) == NULL ||
      (ray->pos_i = malloc(sizeof(int) * 2)) == NULL)
    return (NULL);
  ray->x_win = x;
  ray->cam_x = 2 * x / (double)(WIDTH) - 1;
  ray->ray_x = data->x_pos;
  ray->ray_y = data->y_pos;
  ray->dir_x = ray->cam_x * data->x_cam + data->x_dir;
  ray->dir_y = ray->cam_x * data->y_cam + data->y_dir;
  return (ray);
}
