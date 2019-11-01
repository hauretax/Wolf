/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:12:05 by hutricot          #+#    #+#             */
/*   Updated: 2019/11/01 15:58:07 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_key_53(void)
{
	exit(0);
}

void	ft_key_49_is_playing(t_all *al)
{
	al->p.is_playing = 0;
	ft_print_map(al);
}

void	ft_key_14(t_all *al)
{
	al->p.c_o += al->p.s / 2;
	ft_raycasting(al);
}

void	ft_key_12(t_all *al)
{
	al->p.c_o -= al->p.s / 2;
	ft_raycasting(al);
}

void	ft_deal_key_split_init(t_all *al)
{
	al->p.x = 0;
	al->p.y = 0;
	al->p.tmp = 0;
	al->p.distance = 0;
	al->p.cos = cos(al->p.radian);
	al->p.sin = sin(al->p.radian);
}

void	ft_deal_key_split(t_all *al, double x, double y)
{
	al->p.radian = al->p.c_o;
	al->p.pw = 0;
	while (al->p.radian < M_PI + al->p.c_o - M_PI / WIDTH * 3)
	{
		ft_deal_key_split_init(al);
		while (al->p.tmp < 40 && al->p.distance < 0.01)
		{
			al->p.y = al->p.tmp;
			al->p.x = al->p.tmp * al->p.cos - al->p.y * al->p.sin + al->p.cx;
			al->p.y = al->p.tmp * al->p.sin + al->p.y * al->p.cos + al->p.cy;
			al->p.tmp += 0.001;
			al->p.distance = sqrt((al->p.x - al->p.cx) * (al->p.x - al->p.cx)
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

void	ft_key_125_1(t_all *al)
{
	al->p.cx = -al->p.s * cos(al->p.c_o + 3.14 / 6)
	- -al->p.s * sin(al->p.c_o + 3.14 / 6) + al->p.cx;
	al->p.cy = -al->p.s * sin(al->p.c_o + 3.14 / 6)
	+ -al->p.s * cos(al->p.c_o + 3.14 / 6) + al->p.cy;
	ft_deal_key_split(al, al->p.s * cos(al->p.c_o + 3.14 / 6)
	- al->p.s * sin(al->p.c_o + 3.14 / 6) + al->p.cx,
	al->p.s * sin(al->p.c_o + 3.14 / 6)
	+ al->p.s * cos(al->p.c_o + 3.14 / 6) + al->p.cy);
}

void	ft_key_124_2(t_all *al)
{
	al->p.cx = -al->p.s * cos(al->p.c_o + 3.14 / 6)
	+ -al->p.s * sin(al->p.c_o + 3.14 / 6) + al->p.cx;
	al->p.cy = -al->p.s * sin(al->p.c_o + 3.14 / 6)
	- -al->p.s * cos(al->p.c_o + 3.14 / 6) + al->p.cy;
	ft_deal_key_split(al, al->p.s * cos(al->p.c_o + 3.14 / 6)
	+ al->p.s * sin(al->p.c_o + 3.14 / 6) + al->p.cx,
	al->p.s * sin(al->p.c_o + 3.14 / 6)
	- al->p.s * cos(al->p.c_o + 3.14 / 6) + al->p.cy);
}


void	ft_key_126_13(t_all *al) 
{
	al->p.cx = al->p.s * cos(al->p.c_o + 3.14 / 6)
		- al->p.s * sin(al->p.c_o + 3.14 / 6) + al->p.cx;
	al->p.cy = al->p.s * sin(al->p.c_o + 3.14 / 6)
		+ al->p.s * cos(al->p.c_o + 3.14 / 6) + al->p.cy;
	ft_deal_key_split(al, -al->p.s * cos(al->p.c_o + 3.14 / 6)
			- -al->p.s * sin(al->p.c_o + 3.14 / 6) + al->p.cx,
			-al->p.s * sin(al->p.c_o + 3.14 / 6)
			+ -al->p.s * cos(al->p.c_o + 3.14 / 6) + al->p.cy);
}

void	ft_key_123_0(t_all *al)
{
	al->p.cx = al->p.s * cos(al->p.c_o + 3.14 / 6)
		+ al->p.s * sin(al->p.c_o + 3.14 / 6) + al->p.cx;
	al->p.cy = al->p.s * sin(al->p.c_o + 3.14 / 6)
		- al->p.s * cos(al->p.c_o + 3.14 / 6) + al->p.cy;
	ft_deal_key_split(al, -al->p.s * cos(al->p.c_o + 3.14 / 6)
			+ -al->p.s * sin(al->p.c_o + 3.14 / 6) + al->p.cx,
			-al->p.s * sin(al->p.c_o + 3.14 / 6)
			- -al->p.s * cos(al->p.c_o + 3.14 / 6) + al->p.cy);
}


void	ft_key_49(t_all *al)
{
	al->p.is_playing = 1;
	ft_raycasting(al);
}

void	ft_deal_key_is_playing(t_all *al, int key)
{
	if (key == 49)
		ft_key_49_is_playing(al);
	else if (key == 14)
		ft_key_14(al);
	else if (key == 12)
		ft_key_12(al);
	else if (key == 126 || key == 13)
		ft_key_126_13(al);
	else if (key == 123 || key == 0)
		ft_key_123_0(al);
	else if (key == 125 || key == 1)
		ft_key_125_1(al);
	else if (key == 124 || key == 2)
		ft_key_124_2(al);
}

int		ft_deal_key(int key, t_all *al)
{
	if (key == 53)
		ft_key_53();
	else if (al->p.is_playing == 1)
		ft_deal_key_is_playing(al, key);
    else if (key == 49)
		ft_key_49(al);
	return (0);
}