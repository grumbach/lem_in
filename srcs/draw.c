/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 13:37:28 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/21 08:49:37 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_viewer.h"

/*
** init mlx win and img
*/

void	ft_init_img(t_mlx *mlx)
{
	int		bpp;
	int		sl;
	int		endian;

	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "see ants");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->data = mlx_get_data_addr(mlx->img, &bpp, &sl, &endian);
	mlx->bpp = bpp;
	mlx->sl = sl;
	mlx->endian = endian;
}		

/*
** get first line, init mlx, init controls, init rooms
*/

int		main(void)
{
	t_mlx   mlx;
	t_ants  ants;
	char	parameters[7][11];
	
	ft_bzero(parameters, sizeof(parameters));
	parse_first_line(&ants);//, parameters);
	ft_init_img(&mlx);
	ants.mlx = &mlx;
	reset_controls(&ants.param);
	init_rooms(&ants);
	return (0);
}

/*
** rooms, maxname, maxlinks, min.x, max.x, smin.y, max.y
** ex: 6 7 3 -4 8 -1 5, commented to avoid entering params each time
*/

void	parse_first_line(t_ants *ants)//, char parameters[7][11])
{
/*	char	*s;
	t_xy	i;

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
	}*/
	ants->rooms_nb = 6;//ft_atoi(parameters[0]);
	ants->maxname = 7;//ft_atoi(parameters[1]);
	ants->maxlinks = 3;//ft_atoi(parameters[2]);
	ants->min.x = -4;//ft_atoi(parameters[3]);
	ants->max.x = 8;//ft_atoi(parameters[4]);
	ants->min.y = -1;//ft_atoi(parameters[5]);
	ants->max.y = 5;//ft_atoi(parameters[6]);
	ants->dim.y = ants->max.y - ants->min.y + 1;
	ants->dim.x = ants->max.x - ants->min.x + 1;
}

/*
** roomname y x type links with brackets
** baba 5 6 1 [2][3][4]
*/

void	parse_rooms(t_ants *ants, char name[ants->rooms_nb][ants->maxname + 1],
	t_rooms rooms[ants->rooms_nb])
{
	char	*line;
	t_xy	i;

	i.y = -1;
	while (++i.y < ants->rooms_nb)
	{
		get_next_line(0, &line);
		i.x = 0;
		while (*line && *line != ' ')
			name[i.y][i.x++] = *line++;
		name[i.y][i.x] = '\0';
		rooms[i.y].roomname = name[i.y];
		rooms[i.y].pos.y = ft_atoi(line);
		while (*line && *line != ' ' && *line != '\n')
			++line;
		line = line + 2;
		rooms[i.y].pos.x = ft_atoi(line);
		while (*line && *line != ' ' && *line != '\n')
			++line;
		line = line + 2;	
	//	ft_printf("%d %d", rooms[i.y].pos.y, rooms[i.y].pos.x);
		rooms[i.y].type = ft_atoi(line);
	//	ft_printf("%d", rooms[i.y].type);
		line = line + 2;
		parse_links(ants, rooms, line, i.y);
	}
//	ft_printf("%d %d", rooms[0].pos.y);
}

void	parse_links(t_ants *ants, t_rooms rooms[ants->rooms_nb], char *line, int room_index)
{
	int		links[ants->rooms_nb][ants->maxlinks];
	int		i;

	rooms[room_index].links = (int *)links;
	i = 0;
	++line;
	while (*line && *line != '\n')
	{
		if (*line == '[')
			++line;
		links[room_index][i] = ft_atoi(line);
	//	ft_printf("%d", links[room_index][i]);
		while (*line && *line != '[' && *line != '\n')
			++line;
		++i;
	}
}

/*
**	initialize rooms
*/

void	init_rooms(t_ants *ants)
{
	int     map[ants->dim.y][ants->dim.x];
	char	names[ants->rooms_nb][ants->maxname + 1];
	int		links[ants->rooms_nb][ants->maxlinks];
	t_rooms	rooms[ants->rooms_nb];

//	ft_printf("nb of rooms: %d\nlongest name: %d\nlinks max: %d\nmin/max x : (%d %d), min/max y : (%d %d),\n dim x y : (%d %d)\n",
//		ants->rooms_nb, ants->maxname, ants->maxlinks, ants->min.x, ants->max.x, ants->min.y, ants->max.y, ants->dim.x, ants->dim.y);
	ft_bzero(map, sizeof(map));
	ft_bzero(rooms, sizeof(rooms));
	ft_bzero(names, sizeof(names));
	ft_bzero(links, sizeof(links));
	ants->map_pointer = map;
	ants->rooms_pointer = rooms;
	ants->rooms_nb = 1;///////////////////
	parse_rooms(ants, names, rooms);
//		map[rooms[i.y].pos.y][rooms[i.y].pos.x] = rooms[i.y].type;
	ft_putnbr(rooms[0].pos.y);//
	hook_exposure(ants);
}


/*
** ants rooms are declared on the stack
** function sleeps while awaiting user inputs
*/

void	hook_exposure(t_ants *ants)
{
	mlx_hook(ants->mlx->win, KEYPRESS, KEYPRESSMASK, hook, ants);
	mlx_hook(ants->mlx->win, KEYRELEASE, KEYRELEASEMASK, hook_move, ants);
	mlx_loop_hook(ants->mlx->mlx, draw_ants, ants);
	mlx_loop(ants->mlx->mlx);
}

/*
** function to draw ants and rooms
*/

int		draw_ants(t_ants *ants)
{
	mlx_destroy_image(ants->mlx->mlx, ants->mlx->img);
	ants->mlx->img = mlx_new_image(ants->mlx->mlx, WIDTH, HEIGHT);
	draw_rooms(ants);
	mlx_put_image_to_window(ants->mlx->mlx, ants->mlx->win, ants->mlx->img, 0, 0);
	return (0);
}

/*
** function to draw each room, if it exists
** room are resized.
** room_size will then take the beggest between x and y to have square room
** (in fact spheres)
*/

void	draw_rooms(ANTS)
{
	t_rooms	(*rooms)[ants->rooms_nb];
	int		i;

	rooms = ants->rooms_pointer;
//	rooms = ants->rooms_pointer;
	ants->room_dim.y = (int)(ants->param.scaling * (double)HEIGHT / ((double)ants->dim.y + 3)); 
	ants->room_dim.x = (int)(ants->param.scaling * (double)WIDTH / ((double)ants->dim.x + 3));
	ants->room_size = ants->room_dim.y < ants->room_dim.x ? ants->room_dim.y : ants->room_dim.x;
//	ft_putnbr(ants->room_dim.x);
	i = -1;
	while (++i < ants->rooms_nb)
		draw_room(ants, rooms, i);
}

/*
** function to draw the room
** baba 5 6 1 [2][3][4]
*/

void	draw_room(ANTS, void *room, int n)
{
	t_rooms	(*rooms)[ants->rooms_nb];
	t_xy	i;
	float	radius_squared;

	rooms = room;
	ft_putnbr((*rooms)[0].pos.y);//
	ft_putendl((*rooms)[0].roomname);//
	radius_squared = (ants->room_size >> 1) * (ants->room_size >> 1);
	ft_putnbr(radius_squared);//
	i.y = ants->room_size * ((*rooms)[n].pos.y + 2);
	while (i.y < ants->room_size * ((*rooms)[n].pos.y + 3))
	{
		i.x = ants->room_dim.x * ((*rooms)[n].pos.x + 2);
		while (i.x < ants->room_size * ((*rooms)[n].pos.x + 3))
		{
	//		if (((i.x * i.x) + (i.y * i.y)) <= radius_squared * 1.60)
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