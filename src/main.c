/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:15:31 by hutricot          #+#    #+#             */
/*   Updated: 2019/11/07 15:15:55 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "wolf.h"


int		ft_exit(void)
{
	write(2, "Error! Something wrong\n", 23);
	exit(0);
}

/*
** MX and MG be define in include/wolf.h
*/

void	ft_init(t_all *al, char **av)
{
	al->u.fd = open(av[1], 0);
	read(al->u.fd, al->u.map, 1640);
	al->u.map[1640] = 0;
	al->m.ptr = mlx_init();
	al->p.cx = 0.5;
	al->p.cy = 0.5;
	al->p.s = 0.1;
	al->p.is_playing = 0;
	al->p.c_o = 0.25;
	al->u.map[0] = '1';
	if (!(al->m.isky = MX(al->m.ptr, "./t/skybox.xpm", &al->u.sw, &al->u.sh)))
		ft_exit();
	al->m.ssky = (int*)MG(al->m.isky, &al->m.bpp, &al->m.sl, &al->m.e);
	al->m.win = mlx_new_window(al->m.ptr, WIDTH, HEIGHT, "mlx wolf3d");
}

int		main(int ac, char **av)
{
	t_all al;

	if (ac == 2)
	{
		ft_init(&al, av);
		ft_check_map(&al);
		ft_print_map(&al);
		mlx_hook(al.m.win, 2, 0, ft_deal_key, &al);
		mlx_hook(al.m.win, 6, 0, ft_mouse_motion, &al);
		mlx_hook(al.m.win, 17, 0, ft_exit, (void *)0);
		mlx_loop(al.m.ptr);
	}/*
	else
		ft_exit();*/
	return (0);
}