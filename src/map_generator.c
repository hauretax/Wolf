/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 13:30:22 by hutricot          #+#    #+#             */
/*   Updated: 2019/11/01 13:34:08 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"


void	ft_map_generator_init(t_all *al)
{
	al->v.j = 0;
	al->v.i = 0;
	mlx_clear_window(al->m.ptr, al->m.win);
	al->p.camera_x = 0.5;
	al->p.camera_y = 0.5;
	while (al->v.i < 1639)
	{
		if (al->u.map[al->v.i] != '\n')
			al->u.map[al->v.i] = '0';
		al->v.i++;
	}
	al->v.i = 1;
	ft_set_wall(al->u.map, al->v.i);
}



void	ft_map_generator(t_all *al)
{
	ft_map_generator_init(al);
	while (al->v.i < 1639)
	{
		ft_map_generator_split(al);
		ft_map_generator_end(al);
	}
	ft_map_generator_to_zero(al);
	ft_print_map(al);
}