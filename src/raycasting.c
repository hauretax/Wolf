/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 15:10:35 by hutricot          #+#    #+#             */
/*   Updated: 2019/11/12 13:23:01 by hutricot         ###   ########.fr       */
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
** win like winner not like window
*/

void	win(t_all *al)
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

void	raycasting(t_all *al)
{
	int i;

	i = 0;
	while (++i < WIDTH * HEIGHT)
		al->m.str[i] = 0x000000;
	al->p.radian = al->p.c_o;
	al->p.pw = 0;
	while (al->p.radian < M_PI / 3 + al->p.c_o - (M_PI / 3) / WIDTH)
	{
		init_ray(al);
		while (al->p.tmp < 40)
		{
			find_wall(al);
			if (draw(al) == 1)
				break ;
		}
		al->p.pw++;
		al->p.radian += (M_PI / 3) / WIDTH;
	}
	i = 0;
	win(al);
}
