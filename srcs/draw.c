/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 13:37:28 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/16 15:24:42 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_viewer.h"

void	ft_init_img(t_mlx *mlx)
{
	int		bpp;
	int		sl;
	int		endian;

	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->data = mlx_get_data_addr(mlx->img, &bpp, &sl, &endian);
	mlx->bpp = bpp;
	mlx->sl = sl;
	mlx->endian = endian;
}

int		main(void)
{
	t_mlx   mlx;
	t_ants  ants;

	//mlx = NULL;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "see ants");
	ft_init_img(&mlx);
	ants.rooms_nb = 8; // valeur envoyee par Anselme
	ants.max = (t_xy) {.x = 8, .y = 10}; // valeur envoyee par Anselme
	ants.min = (t_xy) {.x = 0, .y = 2}; // valeur envoyee par Anselme
	ants.mlx = &mlx;
    ants.dim.y = ants.max.y - ants.min.y + 1;
    ants.dim.x = ants.max.x - ants.min.x + 1;
	hook_exposure(&ants);
	return (0);
}

void	reset_controls(t_param *param)
{
	param->scaling = 1;
}

/*
** function sleeps while awaiting user inputs
*/

void	hook_exposure(t_ants *ants)
{
    int     map[ants->dim.y][ants->dim.x];

	reset_controls(&ants->param);
//	mlx_hook(ants->mlx->win, KEYPRESS, KEYPRESSMASK, hook, ants);
//	mlx_hook(ants->mlx->win, KEYRELEASE, KEYRELEASEMASK, hook_move, ants);
	//mlx_loop_hook2(ants->mlx->mlx, draw_ants, ants, map);
	draw_ants(ants, map);
	mlx_loop(ants->mlx->mlx);
}


/*
** 82 and 29 are 0, to reset. 53 is ESC
** 69 is + amd 78 is -
*/

int		hook(int k, t_ants *ants)
{
	hook_move(k, ants);
//	if (k == 82 || k == 29)
//		ft_init(e);
	if (k == 49 )
	{
		mlx_clear_window(ants->mlx->mlx, ants->mlx->win);
		reset_controls(&ants->param);
	}
	else if (k == 53)
		exit(1);
	if (k == 69)
		ants->param.scaling *= 1.25;
	else if (k == 78 && ants->param.scaling > 0.05)
		ants->param.scaling *= 0.9;
	return (0);
}

int		hook_move(int k, t_ants *e)
{
	if (k == K_A || k == K_LEFT)
		e->param.padding = 0 | LEFT;
	else if (k == K_D || k == K_RIGHT)
		e->param.padding = 0 | RIGHT;
	else if (k == K_S || k == K_DOWN)
		e->param.padding = 0 | DOWN;
	else if (k == K_W || k == K_UP)
		e->param.padding = 0 | UP;
	return (0);
}

int		draw_ants(t_ants *ants, ROOMS)
{
	mlx_destroy_image(ants->mlx->mlx, ants->mlx->img);
	ants->mlx->img = mlx_new_image(ants->mlx->mlx, WIDTH, HEIGHT);
//	move(e);
	draw_rooms(ants, map);
	mlx_put_image_to_window(ants->mlx->mlx, ants->mlx->win, ants->mlx->img, 0, 0);
	return (0);
}

/*
** function to draw each room
*/

void	draw_rooms(ANTS, ROOMS)
{
	t_xy	i;

	ants->room_dim.y = (int)(ants->param.scaling * (double)HEIGHT / ((double)ants->dim.y + 3)); 
	ants->room_dim.x = (int)(ants->param.scaling * (double)WIDTH / ((double)ants->dim.x + 3)); 
	i.y = 0;
	while (i.y < ants->room_dim.y)
	{
//		ft_putnbr(i.y);
	//	ft_putchar('\n');
		while (i.x < ants->room_dim.x)
		{
			if (map[i.y][i.x]) // if room exist
				draw_room(i, ants);
			++i.x;
		}
		++i.y;
	}
}

/*
** function to draw the room
*/

void	draw_room(t_xy pos, ANTS)
{
	t_xy	i;

	i.y = ants->room_dim.y * (pos.y + 2);
	while (i.y < ants->room_dim.y * (pos.y + 3))
	{
		i.x = ants->room_dim.x * (pos.x + 2);
		while (i.x < ants->room_dim.x * (pos.x + 3))
		{
			ft_put_pixel(ants->mlx, i.x, i.y, 0xFF0000);
			++i.x;
		}
		++i.y;
	}
}

/*
** color pixel exactly at the right y and x coords if inside the window.
*/

void	ft_put_pixel(t_mlx *m, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
		*(int *)&m->data[((x * m->bpp) >> 3) + (y * m->sl)] = color;
}