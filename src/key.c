/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:12:05 by hutricot          #+#    #+#             */
/*   Updated: 2019/11/11 20:18:32 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	key_when_playing(t_all *al, int key)
{
	if (key == 49)
	{
		al->p.is_playing = 0;
		print_map(al);
	}
	else if (key == 14)
	{
		al->p.c_o += S / 2;
		ft_raycasting(al);
	}
	else if (key == 12)
	{
		al->p.c_o -= S / 2;
		ft_raycasting(al);
	}
	(key == 126 || key == 13) ? axe_y(al , 1) : 0;
	(key == 123 || key == 0) ? right(al, 0) : 0;
	(key == 125 || key == 1) ? axe_y(al, 0) : 0;
	(key == 124 || key == 2) ? right(al, 1) : 0;
}

int		ft_deal_key(int key, t_all *al)
{
	if (key == 53)
		ft_exit(al, 2);
	else if (al->p.is_playing == 1)
		key_when_playing(al, key);
	else if (key == 49)
	{
		al->p.is_playing = 1;
		ft_raycasting(al);
	}
	return (0);
}

/*
** mousse mooving
*/

int		mouse_motion(int x, int y, t_all *al)
{
	if (al->p.is_playing == 1)
	{
		al->p.c_o = (double)x / WIDTH * 6 + y * 0;
		ft_raycasting(al);
	}
	return (0);
}
