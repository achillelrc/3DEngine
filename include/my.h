/*
** hangman.h for  in /home/PierreL/delivery/semestre_2/last_colle/CPE_2016_stumper8
** 
** Made by pierre leleu
** Login   <PierreL@epitech.net>
** 
** Started on  Wed Jun  7 12:21:32 2017 pierre leleu
** Last update Mon Jun 12 12:13:59 2017 Laroche Achille
*/

#ifndef MY_H_
# define MY_H_

# define WIDTH		1024
# define HEIGHT		600

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <SFML/Graphics.h>
# include <SFML/Audio.h>
# include <math.h>

int			**Map;

typedef struct		s_data
{
  int			mapx;
  int			mapy;
  double		front_speed;
  double		rot_speed;
  double		x_pos;
  double		y_pos;
  double		x_dir;
  double		y_dir;
  double		x_cam;
  double		y_cam;
  int			x;
}			t_data;

typedef struct		s_ray
{
  int			x_win;
  double		cam_x;
  double		ray_x;
  double		ray_y;
  double		dir_x;
  double		dir_y;
  int			*steps;
  double		*sides;
  int			*pos_i;
  int			is_side;
}			t_ray;

typedef struct		s_rend
{
  sfRenderWindow	*win;
  sfTexture		*texture;
  sfSprite		*sprite;
}			t_rend;

int		main(int, char **);
void		my_put_pixel(sfUint8 *, int, int, sfColor);
void		my_draw_line(sfUint8 *, sfVector2i, sfVector2i, sfColor);
sfUint8*	create_pixel_buffer(int, int);
sfRenderWindow	*create_window(char *, int, int);
t_rend		*init_render();
t_data		*init_data(int *);
t_ray		*fill_ray(t_data *, int);
double		grab_wall_dist(t_ray *, double, double, int);
double		get_wall_dist(t_ray *, double, double);
sfColor		choose_color(t_ray *);
void		draw_ray(t_ray *, t_rend *, sfUint8 *);
void		mov_cam(t_data *, int);
void		rot_cam(t_data *, int);
int		wolf(t_data *, t_rend *);

int		**get_file(int, int *, int *);
int		**convfile(char **, int, int);
char		*get_next_line(const int);
char		*realloc_and_add(char *, char);

#endif /* !MY_H_ */
