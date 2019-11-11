/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:10:35 by hutricot          #+#    #+#             */
/*   Updated: 2019/11/11 20:04:33 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_ray(t_all *al)
{
	al->p.x = 0;
	al->p.y = 0;
	al->p.tmp = 0;
	al->p.d = 0;
	al->p.cos = cos(al->p.radian);
	al->p.sin = sin(al->p.radian);
}

void	find_wall(t_all *al)
{
	al->x_save = al->p.x;
	al->y_save = al->p.y;
	al->p.y = al->p.tmp;
	al->p.x = al->p.tmp * al->p.cos - al->p.y * al->p.sin + al->p.cx;
	al->p.y = al->p.tmp * al->p.sin + al->p.y * al->p.cos + al->p.cy;
	al->p.tmp += 0.001;
}

/*
**  HEIGHT have been choos for height of wall
** is why we have DE * HEIGHT to calculate height of wall on screen
*/

void	ft_raycasting_init_4(t_all *al)
{
	
	al->p.d = al->p.d * cos(al->p.c_o + M_PI / 6 - al->p.radian);
	al->u.h_p = (DE * HEIGHT/ al->p.d);
	al->t= (HEIGHT / 2 + al->u.h_p / 2) - (HEIGHT / 2 - al->u.h_p / 2);
	if (al->t> HEIGHT)
		al->t= al->t- HEIGHT;
	else
		al->t= 0;
	al->v.i = 0;
	al->sy = HEIGHT / ((HEIGHT / 2 + al->u.h_p / 2)
	- (HEIGHT / 2 - al->u.h_p / 2));
	al->n = 0;
	if (al->u.h_p > HEIGHT)
		al->u.h_p = HEIGHT;
	else if (al->u.h_p < 0)
		al->u.h_p = 0;
}

void	ft_raycasting_init_5(t_all *al)
{
	al->p.d = al->p.d * cos(al->p.c_o + M_PI / 6
	- al->p.radian);
	al->u.h_p = (DE * HEIGHT/ al->p.d);
	if (al->u.h_p > HEIGHT)
		al->u.h_p = HEIGHT;
	else if (al->u.h_p < 0)
		al->u.h_p = 0;
	al->v.i = 0;
}

void	draw_skybox(t_all *al)
{
	while (al->v.i < HEIGHT / 2 - (al->u.h_p / 2))
	{
		al->m.str[al->p.pw + (int)al->v.i * WIDTH] =
		al->m.ssky[abs((int)(al->p.pw + al->p.c_o
		* (180.0 / M_PI) * al->u.sw / 360) + (int)((al->v.i + 512)
		* al->u.sw))];
		al->v.i++;
	}
}

void	draw_land(t_all *al)
{
	while (al->v.i < HEIGHT)
	{
		al->m.str[al->p.pw + (int)al->v.i * WIDTH] = 0x944C00
		- al->v.i / 4;
		al->v.i++;
	}
}

/*
**posisbliter d implemanter les coin 
** pour le moment c est moche
**if (fmod (al->p.x, 1) < 0.001 && fmod (al->p.x, 1) > -0.001 && 
**fmod (al->p.y, 1) < 0.001 && fmod (al->p.y, 1) > -0.001)
**		while (++al->v.i < (HEIGHT / 2 + (al->u.h_p / 2)))
**			al->m.str[al->p.pw + (int)al->v.i * WIDTH] = 0x000000;
*/

void	draw_wall(t_all *al)
{
	int colour;
	int i;

	i = 0;
	if (abs((int)al->x_save - (int)al->p.x) >= abs((int)al->y_save - (int)al->p.y))
		colour = (al->p.cx <= al->p.x)? 0xff0000 : 0x0015ff;
	if (abs((int)al->x_save - (int)al->p.x) <= abs((int)al->y_save - (int)al->p.y))
		colour = (al->p.cy <= al->p.y)? 0x1aff00 : 0x951ABC;
	while (++i < 5 - al->p.d / 2)
		al->m.str[al->p.pw + (int)++al->v.i * WIDTH] = 0x000000;
	while (++al->v.i < (HEIGHT / 2 + (al->u.h_p / 2)))
		al->m.str[al->p.pw + (int)al->v.i * WIDTH] = colour;
	al->v.i -= i;
	while (--i > 0)
		al->m.str[al->p.pw + (int)++al->v.i * WIDTH] = 0x000000;
}

void	ft_raycasting_end(t_all *al)
{
	int i;

	i = 0;
	if ((int)al->p.cx * (int)al->p.cy == 1521)
	{
		mlx_clear_window(al->m.ptr, al->m.win);
		mlx_string_put(al->m.ptr, al->m.win, WIDTH / 2 - 150,
		HEIGHT / 2 - 5, 0xFFFFFF, "You win ! Press enter to restart");
		al->p.is_playing = 0;
	}
	else
	{
		mlx_put_image_to_window(al->m.ptr, al->m.win, al->m.img, 0, 0);
	}
}

int		ft_raycasting_set_map_str(t_all *al)
{
	al->p.d = sqrt((al->p.x - al->p.cx) * (al->p.x - al->p.cx)
	+ (al->p.y - al->p.cy) * (al->p.y - al->p.cy));
	if (al->p.x >= 40 || al->p.y >= 40 || al->p.y < 0 || al->p.x < 0)
	{
		ft_raycasting_init_4(al);
		draw_skybox(al);
		while (++al->v.i < HEIGHT / 2 + al->u.h_p / 2)
			al->m.str[al->p.pw + (int)al->v.i * WIDTH] = 0x0;
		draw_land(al);
		return (1);
	}
	else if (al->u.map[(int)al->p.x + (int)al->p.y * 41] == '0')
	{
		ft_raycasting_init_5(al);
		draw_skybox(al);
		draw_wall(al);
		draw_land(al);
		return (1);
	}
	return (0);
}

void	ft_raycasting(t_all *al)
{
	int i;

	i = 0;
	while (++i <WIDTH * HEIGHT)
		al->m.str[i] = 0x000000;
	al->p.radian = al->p.c_o;
	al->p.pw = 0;
	while (al->p.radian < M_PI / 3 + al->p.c_o
		- (M_PI / 3) / WIDTH)
	{
		init_ray(al);
		while (al->p.tmp < 40)
		{
			find_wall(al);
			if (ft_raycasting_set_map_str(al) == 1)
				break ;
		}
		al->p.pw++;
		al->p.radian += (M_PI / 3) / WIDTH;
	}
	i = 0;
	ft_raycasting_end(al);
}
