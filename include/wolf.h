/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hutricot <hutricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 11:03:11 by hutricot          #+#    #+#             */
/*   Updated: 2019/11/06 19:51:00 by hutricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include   <fcntl.h>
# include   <sys/types.h>
# include   <sys/uio.h>
# include   <unistd.h>
# include   <stdlib.h>
# include   <mlx.h>
# include   <math.h>
# define    WIDTH 1200
# define    HEIGHT 1000
# define    MX   mlx_xpm_file_to_image
# define    MG   mlx_get_data_addr
# define    MPP  mlx_pixel_put
# define    MSP  mlx_string_put

typedef struct  s_mlx
{
	void	*ptr;
	void	*win;
	void	*img;
	int		*str;
	void	*isky;
	int		*ssky;
	void	*img_wall;
	int		*str_wall;
	int		bpp;
	int		sl;
	int		e;
}               t_mlx;

/*
** ppx = player position x
** ppy = player position y
** c_o = cameras orientation
** cx = cameras x
** c_y = camera y
** pw = pixel width
** de = distance ecran
*/

typedef struct   s_pla
{
	double	s;
	double	x;
	double	y;
	double	cx;
	double	cy;
	double	radian;
	double	d;
	double	tmp;
	double	sin;
	double	cos;
	double	c_o;
	double	de;
    int     pw;
	int		is_playing;
	int		ppx;
	int		ppy;
}                t_pla;

typedef struct  s_var
{
    int j;
    int i;
    int k;
    int r;
}              t_var;


/*
** first : s = sky w = wall second : w = width h = heigth 
** exemple : sw = sky width 
** hm = hauteur_mur
** hp = hauteur prevus
*/

typedef struct   s_uti
{
    int		fd;
	char	map[1641];
	int		sw;
	int		sh;
	int		ww;
	int		wh;
    int     h_m;
    int     h_p;
}                t_uti;

/*
** tout les valeur poser dans la struc principale son a deplacer ailleur je supoose pouvoir reduire leur utilisation a une fonciton
*/

typedef struct	s_all
{
    t_mlx   m;
    t_pla   p;
    t_uti   u;
    t_var   v;
    double  x_save;
    double  y_save;
    double  sy;
    double  sx;
    double  t;
    double  n;
}				t_all;

/*
** creat a map
*/

void	ft_check_map(t_all *al);
void	ft_print_map(t_all *al);

/*
** generting map
*/

void	ft_map_generator_init(t_all *al);
void	ft_map_generator(t_all *al);

/*
** using key
*/

int		ft_deal_key(int key, t_all *al);
int		ft_mouse_motion(int x, int y, t_all *al);

/*
**print on sccreen
*/

void	ft_raycasting(t_all *al);

int		ft_exit(void);

#endif