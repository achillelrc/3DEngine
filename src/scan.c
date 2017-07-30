/*
** scan.c for scanner in /home/binary/All/Wolf3D/Wolf/MY/wolf3d
** 
** Made by Laroche Achille
** Login   <binary@epitech.net>
** 
** Started on  Mon Jun 12 15:18:38 2017 Laroche Achille
** Last update Mon Jun 12 15:28:48 2017 Laroche Achille
*/

#include "my.h"

double		grab_wall_dist(t_ray *ray, double dx, double dy, int hit)
{
  while (hit == 0)
    {
      if (ray->sides[0] < ray->sides[1])
	{
	  ray->sides[0] += dx;
	  ray->pos_i[0] += ray->steps[0];
	  ray->is_side = 0;
	}
      else
	{
	  ray->sides[1] += dy;
	  ray->pos_i[1] += ray->steps[1];
	  ray->is_side = 1;
	}
      if (Map[ray->pos_i[0]][ray->pos_i[1]] > 0)
	hit = 1;
    }
  dx = ray->pos_i[1] - ray->ray_y;
  if (ray->is_side == 0)
    dx = ray->pos_i[0] - ray->ray_x;
  if (ray->is_side == 0)
    return (fabs((dx + (1 - ray->steps[0]) / 2) / ray->dir_x));
  else
    return (fabs((dx + (1 - ray->steps[1]) / 2) / ray->dir_y));
}

double		get_wall_dist(t_ray *ray, double dx, double dy)
{
  ray->pos_i[0] = (int)(ray->ray_x);
  ray->pos_i[1] = (int)(ray->ray_y);
  ray->steps[0] = 1;
  ray->steps[1] = 1;
  if (ray->dir_x < 0)
    ray->sides[0] = dx * (ray->ray_x - ray->pos_i[0]);
  else
    ray->sides[0] = dx * (1.0 + ray->pos_i[0] - ray->ray_x);
  if (ray->dir_y < 0)
    ray->sides[1] = dy * (ray->ray_y - ray->pos_i[1]);
  else
    ray->sides[1] = dy * (1.0 + ray->pos_i[1] - ray->ray_y);
  if (ray->dir_x < 0)
    ray->steps[0] = -1;
  if (ray->dir_y < 0)
    ray->steps[1] = -1;
  return (grab_wall_dist(ray, dx, dy, 0));
}

void		draw_ray(t_ray *ray, t_rend *render, sfUint8* pixels)
{
  sfVector2i	from;
  sfVector2i	to;
  int		tmp;
  double	delta_x;
  double	delta_y;
  double	wall_dist;

  delta_x = sqrt(1 + (ray->dir_y * ray->dir_y) / (ray->dir_x * ray->dir_x));
  delta_y = sqrt(1 + (ray->dir_x * ray->dir_x) / (ray->dir_y * ray->dir_y));
  wall_dist = get_wall_dist(ray, delta_x, delta_y);
  tmp = (int)(HEIGHT / wall_dist);
  from.x = ray->x_win;
  to.x = ray->x_win;
  from.y = (tmp * -1) / 2 + (HEIGHT / 2);
  to.y = tmp / 2 + (HEIGHT / 2);
  if (from.y < 0)
    from.y = 0;
  if (to.y >= HEIGHT)
    to.y = HEIGHT - 1;
  my_draw_line(pixels, from, to, choose_color(ray));
  sfTexture_updateFromPixels(render->texture, pixels, WIDTH, HEIGHT, 0, 0);
  free(ray);
}

void		mov_cam(t_data *data, int dif)
{
  double	sp;

  sp = data->front_speed;
  if (dif == 1)
    {
      if (Map[(int)(data->x_pos + data->x_dir * sp)][(int)(data->y_pos)] == 0)
	data->x_pos += data->x_dir * sp;
      if (Map[(int)(data->x_pos)][(int)(data->y_pos + data->y_dir * sp)] == 0)
	data->y_pos += data->y_dir * sp;
    }
  else
    {
      if (Map[(int)(data->x_pos - data->x_dir * sp)][(int)(data->y_pos)] == 0)
	data->x_pos -= data->x_dir * sp;
      if (Map[(int)(data->x_pos)][(int)(data->y_pos - data->y_dir * sp)] == 0)
	data->y_pos -= data->y_dir * sp;
    }
}

void		rot_cam(t_data *data, int div)
{
  double	rot;
  double	tmpcam;
  double	tmpdir;

  rot = data->rot_speed * div;
  tmpdir = data->x_dir;
  data->x_dir = data->x_dir * cos(rot) - data->y_dir * sin(rot);
  data->y_dir = tmpdir * sin(rot) + data->y_dir * cos(rot);
  tmpcam = data->x_cam;
  data->x_cam = data->x_cam * cos(rot) - data->y_cam * sin(rot);
  data->y_cam = tmpcam * sin(rot) + data->y_cam * cos(rot);
}
