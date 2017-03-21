/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 13:37:28 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/21 04:32:44 by angavrel         ###   ########.fr       */
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



/*
** mlx & params initializations & main program (hook_exposure) launch
*/

int		main(void)
{
	t_mlx   mlx;
	t_ants  ants;
	char	parameters[7][11];
	char	*s;
	t_xy	i;

	//mlx = NULL;
	/*
	if (size.gflag)
		ft_printf("%d %d %d %d %d %d %d\n", size.rooms, size.maxname, \

		6 7 3 -4 8 -1 5
		

		size.maxlinks, size.min.x, size.max.x, size.min.y, size.max.y);*/
	
	ft_bzero(parameters, sizeof(parameters));
	get_next_line(0, &s);
	i.y = 0;
	while (*s && *s != '\n')
	{
		i.x = -1;
		if (*s == ' ')
			++s;
		while (*s && *s != ' ' && *s != '\n')
			parameters[i.y][++i.x] = *s++;
		++i.y;
	}
	ants.rooms_nb = ft_atoi(parameters[0]);
	ants.maxname = ft_atoi(parameters[1]);
	ants.maxlinks = ft_atoi(parameters[2]);
	ants.min.x = ft_atoi(parameters[3]);
	ants.max.x = ft_atoi(parameters[4]);
	ants.min.y = ft_atoi(parameters[5]);
	ants.max.y = ft_atoi(parameters[6]);
	ants.dim.y = ants.max.y - ants.min.y + 1;
	ants.dim.x = ants.max.x - ants.min.x + 1;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "see ants");
	ft_init_img(&mlx);
	ft_putchar('y');
	reset_controls(&ants.param);
	ft_putchar('u');
	init_rooms(&ants);
	ft_putchar('v');
	return (0);
}

void	parse_rooms(t_ants *ants, int map[ants->dim.y][ants->dim.x]
{
	int		room_index;
	char	*line;
	t_xy	i;

	room_index = -1;
	while (++room_index < ants->rooms_nb)
	{
		get_next_line(0, &line);
		while (*s && *s != '\n')
		{
			parse_room_name(&line);
			parse_room_links(&line);
			parse_room_pos(&line, map);

		}
	}
}


/*
**	initialize rooms
*/

void	init_rooms(t_ants *ants)
{
	int     map[ants->dim.y][ants->dim.x];
	t_rooms	rooms[ants->rooms_nb];

//	ft_printf("nb of rooms: %d\nlongest name: %d\nlinks max: %d\nmin/max x : (%d %d), min/max y : (%d %d),\n dim x y : (%d %d)\n",
//		ants->rooms_nb, ants->maxname, ants->maxlinks, ants->min.x, ants->max.x, ants->min.y, ants->max.y, ants->dim.x, ants->dim.y);
	ft_putchar('v');
	ft_bzero(map, sizeof(map));
	ft_putchar('l');
	ft_bzero(rooms, sizeof(rooms));
	ft_putchar('r');
	ants->map_pointer = map;
//	rooms[0].pos = (t_xy) {.y = 5, .x = 4};
//	rooms[0].type = 1;
//	rooms[1].pos = (t_xy) {.y = 5, .x = 4};
//	rooms[1].type = 2;;

	parse_rooms(ants, map);
//		map[rooms[i.y].pos.y][rooms[i.y].pos.x] = rooms[i.y].type;
	hook_exposure(ants);
	ft_putchar('d');

	
}


/*
** ants rooms are declared on the stack
** function sleeps while awaiting user inputs
*/

void	hook_exposure(t_ants *ants)
{
    
	ft_putchar('a');
	mlx_hook(ants->mlx->win, KEYPRESS, KEYPRESSMASK, hook, ants);
	mlx_hook(ants->mlx->win, KEYRELEASE, KEYRELEASEMASK, hook_move, ants);
	mlx_loop_hook(ants->mlx->mlx, draw_ants, ants);
	draw_ants(ants);
	mlx_loop(ants->mlx->mlx);
}

/*
** function to draw ants and rooms
*/

int		draw_ants(t_ants *ants)
{
	ft_putchar('b');
	mlx_destroy_image(ants->mlx->mlx, ants->mlx->img);
	ants->mlx->img = mlx_new_image(ants->mlx->mlx, WIDTH, HEIGHT);
	draw_rooms(ants);
	mlx_put_image_to_window(ants->mlx->mlx, ants->mlx->win, ants->mlx->img, 0, 0);
	return (0);
}

/*
** function to draw each room, if it exists
*/

void	draw_rooms(ANTS)
{
	int     (*map)[ants->dim.y][ants->dim.x];

	ft_putchar('c');
	map = ants->map_pointer;
	t_xy	i;
	ants->room_dim.y = (int)(ants->param.scaling * (double)HEIGHT / ((double)ants->dim.y + 3)); 
	ants->room_dim.x = (int)(ants->param.scaling * (double)WIDTH / ((double)ants->dim.x + 3));
	ants->room_size = ants->room_dim.y < ants->room_dim.x ? ants->room_dim.y : ants->room_dim.x;
	ft_putnbr(ants->room_dim.x);
	i.y = 0;
	while (i.y < ants->room_dim.y)
	{
		i.x = 0;
		while (i.x < ants->room_dim.x)
		{
			if (map[i.y][i.x])
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
	float	radius_squared;
	int     (*map)[ants->dim.y][ants->dim.x];

	ft_putchar('d');
	map = ants->map_pointer;
	radius_squared = (ants->room_size >> 1) * (ants->room_size >> 1);
	i.y = ants->room_size * (pos.y + 2);
	while (i.y < ants->room_size * (pos.y + 3))
	{
		i.x = ants->room_dim.x * (pos.x + 2);
		while (i.x < ants->room_size * (pos.x + 3))
		{
			if (((i.x * i.x) + (i.y * i.y)) <= radius_squared * 1.60)
			ft_put_pixel(ants->mlx, i.x + ants->param.padding.x,
				i.y + ants->param.padding.y, 0xFF0000);
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