/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:53:30 by hutricot          #+#    #+#             */
/*   Updated: 2019/11/12 15:21:03 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
**HEIGHT have been choos for height of wall
**is why we have DE * HEIGHT to calculate height of wall on screen
*/

void	wall_height(t_all *al)
{
	al->p.d = al->p.d * cos(al->p.c_o + M_PI / 6 - al->p.radian);
	al->u.h_p = (DE * HEIGHT / al->p.d);
	al->t = (HEIGHT / 2 + al->u.h_p / 2) - (HEIGHT / 2 - al->u.h_p / 2);
	if (al->t > HEIGHT)
		al->t = al->t - HEIGHT;
	else
		al->t = 0;
	al->v.i = 0;
	al->sy = HEIGHT / ((HEIGHT / 2 + al->u.h_p / 2)
	- (HEIGHT / 2 - al->u.h_p / 2));
	al->n = 0;
	if (al->u.h_p > HEIGHT)
		al->u.h_p = HEIGHT;
	else if (al->u.h_p < 0)
		al->u.h_p = 0;
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
** we can implemante border of bloc
** but is ugly ^^
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
	if (abs((int)al->x_save - (int)al->p.x) > 0)
		colour = (al->p.cx <= al->p.x) ? 0xff0000 : 0x0015ff;
	if (abs((int)al->x_save - (int)al->p.x) == 0)
		colour = (al->p.cy <= al->p.y) ? 0x1aff00 : 0x951ABC;
	while (++i < 5 - al->p.d / 2)
		al->m.str[al->p.pw + (int)++al->v.i * WIDTH] = 0x000000;
	while (++al->v.i < (HEIGHT / 2 + (al->u.h_p / 2)))
		al->m.str[al->p.pw + (int)al->v.i * WIDTH] = colour;
	al->v.i -= i;
	while (--i > 0)
		al->m.str[al->p.pw + (int)++al->v.i * WIDTH] = 0x000000;
}

int		draw(t_all *al)
{
	al->p.d = sqrt((al->p.x - al->p.cx) * (al->p.x - al->p.cx)
	+ (al->p.y - al->p.cy) * (al->p.y - al->p.cy));
	if (al->p.x >= 40 || al->p.y >= 40 || al->p.y < 0 || al->p.x < 0)
	{
		wall_height(al);
		draw_skybox(al);
		while (++al->v.i < HEIGHT / 2 + al->u.h_p / 2)
			al->m.str[al->p.pw + (int)al->v.i * WIDTH] = 0x0;
		draw_land(al);
		return (1);
	}
	else if (al->u.map[(int)al->p.x + (int)al->p.y * 41] == '0')
	{
		wall_height(al);
		draw_skybox(al);
		draw_wall(al);
		draw_land(al);
		return (1);
	}
	return (0);
}
