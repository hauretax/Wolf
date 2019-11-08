/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_a_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 11:56:38 by hutricot          #+#    #+#             */
/*   Updated: 2019/11/08 19:37:28 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_print_player(t_all *al)
{
	double a;
	double b;

	a = (440 / 40 * al->p.cx) + 20;
	b = (440 / 40 * al->p.cy) + 20;
	MPP(al->m.ptr, al->m.win, a, b, 0x004DFF);
	MPP(al->m.ptr, al->m.win, a + 1, b, 0x004DFF);
	MPP(al->m.ptr, al->m.win, a - 1, b, 0x004DFF);
	MPP(al->m.ptr, al->m.win, a + 1, b + 1, 0x004DFF);
	MPP(al->m.ptr, al->m.win, a - 1, b + 1, 0x004DFF);
	MPP(al->m.ptr, al->m.win, a, b - 1, 0x004DFF);
	MPP(al->m.ptr, al->m.win, a, b + 1, 0x004DFF);
	MPP(al->m.ptr, al->m.win, a + 1, b - 1, 0x004DFF);
	MPP(al->m.ptr, al->m.win, a - 1, b - 1, 0x004DFF);
}

void	ft_print_map_split_1(t_all *al)
{
	al->v.k = -1;
	while (++al->v.k <= 10)
	{
		al->v.r = -1;
		while (++al->v.r <= 10)
			MPP(al->m.ptr, al->m.win,
					((al->v.i - al->v.j * 41) * 11) + al->v.r + 20,
					(al->v.j * 11) + al->v.k + 20, 0xD0D0D0);
	}
}

void	ft_print_map_split_2(t_all *al)
{
	al->v.k = -1;
	while (++al->v.k <= 10)
	{
		al->v.r = -1;
		while (++al->v.r <= 10)
			MPP(al->m.ptr, al->m.win,
					((al->v.i - al->v.j * 41) * 11) + al->v.r + 20,
					(al->v.j * 11) + al->v.k + 20, 0x520000);
	}
}

void	ft_print_map(t_all *al)
{
	MSP(al->m.ptr, al->m.win, 500, 200, 0xFFFFFF, "Press 'Space' to play");
	MSP(al->m.ptr, al->m.win, 500, 225, 0xFFFFFF, "Press 'ESC' to exit");
	al->v.i = -1;
	al->v.j = 0;
	while (++al->v.i < 1639)
	{
		if (al->u.map[al->v.i] == '\n')
			al->v.j++;
		if (al->u.map[al->v.i] == '1')
			ft_print_map_split_1(al);
		else if (al->u.map[al->v.i] == '0')
			ft_print_map_split_2(al);
	}
	ft_print_player(al);
}

void	ft_check_map(t_all *al)
{
	int i;
    int j;

    i = 0;
    j = 0;
	while (i < 1639)
	{
		if (al->u.map[i] == '\n')
		{
			if ((i++ - j++) % 40 != 0)
				ft_exit(al,1);
		}
		if (al->u.map[i] != '1' && al->u.map[i] != '0')
			ft_exit(al,1);
	    i++;
	}
	if (al->u.map[1640] != '\0')
		ft_exit(al, 1);
}
