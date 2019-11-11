/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mooving.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:34:00 by hutricot          #+#    #+#             */
/*   Updated: 2019/11/11 20:19:51 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	wall_hitbox(t_all *al, double x, double y)
{
	al->p.radian = al->p.c_o;
	al->p.pw = 0;
	while (al->p.radian < M_PI + al->p.c_o - M_PI / WIDTH * 3)
	{
		init_ray(al);
		while (al->p.tmp < 40 && al->p.d < 0.01)
		{
			al->p.y = al->p.tmp;
			al->p.x = al->p.tmp * al->p.cos - al->p.y * al->p.sin + al->p.cx;
			al->p.y = al->p.tmp * al->p.sin + al->p.y * al->p.cos + al->p.cy;
			al->p.tmp += 0.001;
			al->p.d = sqrt((al->p.x - al->p.cx) * (al->p.x - al->p.cx)
					+ (al->p.y - al->p.cy) * (al->p.y - al->p.cy));
			if (al->p.x >= 40 || al->p.y >= 40 || al->p.y < 0 || al->p.x < 0
					|| al->u.map[(int)al->p.x + (int)al->p.y * 41] == '0')
			{
				al->p.cx = x;
				al->p.cy = y;
				return ;
			}
		}
		al->p.pw++;
		al->p.radian += M_PI / WIDTH * 3;
	}
	ft_raycasting(al);
}

void	axe_y(t_all *al, int a)
{
	if (a == 0)
	{
		al->p.cx = -S * cos(al->p.c_o + 3.14 / 6)
		- -S * sin(al->p.c_o + 3.14 / 6) + al->p.cx;
		al->p.cy = -S * sin(al->p.c_o + 3.14 / 6)
		+ -S * cos(al->p.c_o + 3.14 / 6) + al->p.cy;
		wall_hitbox(al, S * cos(al->p.c_o + 3.14 / 6)
		- S * sin(al->p.c_o + 3.14 / 6) + al->p.cx,
		S * sin(al->p.c_o + 3.14 / 6)
		+ S * cos(al->p.c_o + 3.14 / 6) + al->p.cy);
	}
	if (a == 1)
	{
		al->p.cx = S * cos(al->p.c_o + 3.14 / 6)
		- S * sin(al->p.c_o + 3.14 / 6) + al->p.cx;
		al->p.cy = S * sin(al->p.c_o + 3.14 / 6)
		+ S * cos(al->p.c_o + 3.14 / 6) + al->p.cy;
		wall_hitbox(al, -S * cos(al->p.c_o + 3.14 / 6)
		- -S * sin(al->p.c_o + 3.14 / 6) + al->p.cx,
		-S * sin(al->p.c_o + 3.14 / 6)
		+ -S * cos(al->p.c_o + 3.14 / 6) + al->p.cy);
	}
}

void	right(t_all *al, int a)
{
	if (a == 1)
	{
		al->p.cx = -S * cos(al->p.c_o + 3.14 / 6)
		+ -S * sin(al->p.c_o + 3.14 / 6) + al->p.cx;
		al->p.cy = -S * sin(al->p.c_o + 3.14 / 6)
		- -S * cos(al->p.c_o + 3.14 / 6) + al->p.cy;
		wall_hitbox(al, S * cos(al->p.c_o + 3.14 / 6)
		+ S * sin(al->p.c_o + 3.14 / 6) + al->p.cx,
		S * sin(al->p.c_o + 3.14 / 6)
		- S * cos(al->p.c_o + 3.14 / 6) + al->p.cy);
	}
	if (a == 0)
	{
		al->p.cx = S * cos(al->p.c_o + 3.14 / 6)
		+ S * sin(al->p.c_o + 3.14 / 6) + al->p.cx;
		al->p.cy = S * sin(al->p.c_o + 3.14 / 6)
		- S * cos(al->p.c_o + 3.14 / 6) + al->p.cy;
		wall_hitbox(al, -S * cos(al->p.c_o + 3.14 / 6)
		+ -S * sin(al->p.c_o + 3.14 / 6) + al->p.cx,
		-S * sin(al->p.c_o + 3.14 / 6)
		- -S * cos(al->p.c_o + 3.14 / 6) + al->p.cy);
	}
}
