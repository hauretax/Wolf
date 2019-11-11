/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:15:31 by hutricot          #+#    #+#             */
/*   Updated: 2019/11/11 13:45:33 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		ft_exit(t_all *al, int i)
{
	if (i == 0)
		write(2, "usage : ./wolf3d (maps file)\n", 29);
	if (i == 1)
	{
		write(2, "Error! Something wrong\n", 23);
		mlx_destroy_window(al->m.ptr, al->m.win);
	}
	if (i == 2)
	{
		write(1, "have a good day\n", 16);
		mlx_destroy_image(al->m.ptr, al->m.img);
		mlx_destroy_window(al->m.ptr, al->m.win);
	}
	exit(0);
}

/*
** MX and MG be define in include/wolf.h
*/

void	init_var(t_all *al, char **av)
{
	al->u.fd = open(av[1], 0);
	read(al->u.fd, al->u.map, 1640);
	al->u.map[1640] = 0;
	al->m.ptr = mlx_init();
	al->p.cx = 1.5;
	al->p.cy = 1.5;
	al->p.is_playing = 0;
	al->p.c_o = 0.25;
	al->u.map[0] = '1';
	if (!(al->m.isky = MX(al->m.ptr, "./t/skybox.xpm", &al->u.sw, &al->u.sh)))
		ft_exit(al, 1);
	al->m.ssky = (int*)MG(al->m.isky, &al->m.bpp, &al->m.sl, &al->m.e);
	al->m.win = mlx_new_window(al->m.ptr, WIDTH, HEIGHT, "mlx wolf3d");
	al->m.img = mlx_new_image(al->m.ptr, WIDTH, HEIGHT);
	al->m.str = (int*)MG(al->m.img, &al->m.bpp, &al->m.sl, &al->m.e);
}

int		main(int ac, char **av)
{
	t_all al;

	if (ac == 2)
	{
		init_var(&al, av);
		check_map(&al);
		print_map(&al);
		mlx_hook(al.m.win, 2, 0, ft_deal_key, &al);
		mlx_hook(al.m.win, 6, 0, mouse_motion, &al);
		mlx_hook(al.m.win, 17, 0, ft_exit, (void *)0);
		mlx_loop(al.m.ptr);
	}
	else
		ft_exit(NULL, 0);
	return (0);
}
