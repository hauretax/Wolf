/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:10:35 by hutricot          #+#    #+#             */
/*   Updated: 2019/11/01 15:48:30 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_raycasting_init_1(t_all *al)
{
	al->m.img = mlx_new_image(al->m.ptr, WIDTH, HEIGHT);
	al->m.str = (int*)MG(al->m.img, &al->m.bpp, &al->m.sl, &al->m.e);
	al->p.radian = al->p.c_o;
	al->p.pw = 0;
	al->p.de = 1;
	al->u.h_m= 200;
}

void	ft_raycasting_init_2(t_all *al)
{
	al->p.x = 0;
	al->p.y = 0;
	al->p.tmp = 0;
	al->p.distance = 0;
	al->p.cos = cos(al->p.radian);
	al->p.sin = sin(al->p.radian);
}

void	ft_raycasting_init_3(t_all *al)
{
	al->x_save = al->p.x;
	al->y_save = al->p.y;
	al->p.y = al->p.tmp;
	al->p.x = al->p.tmp * al->p.cos - al->p.y * al->p.sin + al->p.cx;
	al->p.y = al->p.tmp * al->p.sin + al->p.y * al->p.cos + al->p.cy;
	al->p.tmp += 0.001;
	al->p.distance = sqrt((al->p.x - al->p.cx) * (al->p.x - al->p.cx)
	+ (al->p.y - al->p.cy) * (al->p.y - al->p.cy));
}

void	ft_raycasting_init_4(t_all *al)
{
	al->p.distance = al->p.distance * cos(al->p.c_o + M_PI / 6
	- al->p.radian);
	al->u.h_p = (al->p.de * al->u.h_m/ al->p.distance);
	al->t= (HEIGHT / 2 + al->u.h_p / 2) - (HEIGHT / 2
	- al->u.h_p / 2);
	if (al->t> HEIGHT)
		al->t= al->t- HEIGHT;
	else
		al->t= 0;
	al->v.i = 0;
	al->sy = al->u.wh / ((HEIGHT / 2 + al->u.h_p / 2)
	- (HEIGHT / 2 - al->u.h_p / 2));
	al->n = 0;
	if (al->u.h_p > HEIGHT)
		al->u.h_p = HEIGHT;
	else if (al->u.h_p < 0)
		al->u.h_p = 0;
}

void	ft_raycasting_init_5(t_all *al)
{
	al->p.distance = al->p.distance * cos(al->p.c_o + M_PI / 6
	- al->p.radian);
	al->u.h_p = (al->p.de * al->u.h_m/ al->p.distance);
	if (al->u.h_p > HEIGHT)
		al->u.h_p = HEIGHT;
	else if (al->u.h_p < 0)
		al->u.h_p = 0;
	al->v.i = 0;
}

void	ft_raycasting_set_skybox(t_all *al)
{
	while (al->v.i < HEIGHT / 2 - al->u.h_p / 2)
	{
		al->m.str[al->p.pw + (int)al->v.i * WIDTH] =
		al->m.ssky[abs((int)(al->p.pw + al->p.c_o
		* (180.0 / M_PI) * al->u.sw / 360) + (int)((al->v.i + 512)
		* al->u.sw))];
		al->v.i++;
	}
}

void	ft_raycasting_set_land(t_all *al)
{
	while (al->v.i < HEIGHT)
	{
		al->m.str[al->p.pw + (int)al->v.i * WIDTH] = 0x944C00
		- al->v.i / 4;
		al->v.i++;
	}
}

void	ft_raycasting_walls_out_map(t_all *al)
{
	while (al->v.i < HEIGHT / 2 + al->u.h_p / 2)
	{
		al->m.str[al->p.pw + (int)al->v.i * WIDTH] =
		al->m.str_wall[(int)(al->n + al->t/ 2 * al->sy) * al->u.ww];
		al->v.i++;
		al->n = al->n + al->sy;
	}
}

void	ft_raycasting_walls_in_map(t_all *al)
{
	while (al->v.i < HEIGHT / 2 + (al->u.h_p / 2))
	{
		if (abs((int)al->x_save - (int)al->p.x) >= abs((int)al->y_save
			- (int)al->p.y) && al->p.cx <= al->p.x)
			al->m.str[al->p.pw + (int)al->v.i * WIDTH] = 0xff0000;
		else if (abs((int)al->x_save - (int)al->p.x) <= abs((int)al->y_save
			- (int)al->p.y) && al->p.cy <= al->p.y)
			al->m.str[al->p.pw + (int)al->v.i * WIDTH] = 0x1aff00;
		else if (abs((int)al->x_save - (int)al->p.x) >= abs((int)al->y_save
			- (int)al->p.y))
			al->m.str[al->p.pw + (int)al->v.i * WIDTH] = 0x0015ff;
		else if (abs((int)al->x_save - (int)al->p.x) <= abs((int)al->y_save
			- (int)al->p.y))
			al->m.str[al->p.pw + (int)al->v.i * WIDTH] = 0x951ABC;
		al->v.i++;
	}
}

void	ft_raycasting_end(t_all *al)
{
	if ((int)al->p.cx * (int)al->p.cy == 1521)
	{
		mlx_clear_window(al->m.ptr, al->m.win);
		mlx_string_put(al->m.ptr, al->m.win, WIDTH / 2 - 150,
		HEIGHT / 2 - 5, 0xFFFFFF, "You win ! Press enter to restart");
		al->p.is_playing = 0;
	}
	else
		mlx_put_image_to_window(al->m.ptr, al->m.win, al->m.img, 0, 0);
}

int		ft_raycasting_set_map_str(t_all *al)
{
	if (al->p.x >= 40 || al->p.y >= 40 || al->p.y < 0 || al->p.x < 0)
	{
		ft_raycasting_init_4(al);
		ft_raycasting_set_skybox(al);
		ft_raycasting_walls_out_map(al);
		ft_raycasting_set_land(al);
		return (1);
	}
	else if (al->u.map[(int)al->p.x + (int)al->p.y * 41] == '0')
	{
		ft_raycasting_init_5(al);
		ft_raycasting_set_skybox(al);
		ft_raycasting_walls_in_map(al);
		ft_raycasting_set_land(al);
		return (1);
	}
	return (0);
}

void	ft_raycasting(t_all *al)
{
	ft_raycasting_init_1(al);
	while (al->p.radian < M_PI / 3 + al->p.c_o
		- (M_PI / 3) / WIDTH)
	{
		ft_raycasting_init_2(al);
		while (al->p.tmp < 40)
		{
			ft_raycasting_init_3(al);
			if (ft_raycasting_set_map_str(al) == 1)
				break ;
		}
		al->p.pw++;
		al->p.radian += (M_PI / 3) / WIDTH;
	}
	ft_raycasting_end(al);
}