/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_viewer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 00:56:57 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/12 10:40:10 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_viewer.h"

int	main(void)
{
	t_mlx	mlx;
	t_ants	ants;

	ants.room_nb = 8; // valeur envoyee par Anselme
	ants.max.y = 5; // valeur envoyee par Anselme
	ants.max.x = 7; // valeur envoyee par Anselme
	lem_in_parsing(&ants);
	ants.mlx = &mlx;
	ants.mlx->win = mlx_new_window(ants.mlx->mlx, WIDTH, HEIGHT, "see-ants");
	ants.mlx->img = mlx_new_image(ants.mlx->mlx, WIDTH, HEIGHT);
	ants.mlx->data = mlx_get_data_addr(ants.mlx->img, &ants.mlx->bpp,
		&ants.mlx->sl, &ants.mlx->endian);
	hook_exposure(&ants);
	return (0);
}

/*
125
##start
0 5 0
#comment
1 1 0
2 3 2
##end
3 1 3 
0-1
0-2
1-2
2-3
*/

/*
** variable start is to check the position inside the parser
** while start = 0 we parse nb is the nb of ants
** while start = 1 we look for ##start
** while start is between 2 and 4 we parse rooms,
** while start = 5 we parse links
*/

void	lem_in_parsing(ANTS)
{
	char	*line;
	int		start;
	t_rooms	rooms[ants->max.y][ants->max.x];

	start = 0;
	ants->loop = 1;
	init_rooms(ants, rooms);
	while (get_next_line(0, &line) > 0 && ants->loop)
	{
		if (not_comment(line, &start))
		{
			if (start == 0 && ++start)
				ants->nb = ft_atoi(line);
			else if (start < 5)
				add_room(ants, line, start - 1, rooms);
			else if (start > 4)
				parse_links(ants, line);
		}
		else if (!not_comment(line, &start))
			;// we need to store the comment as requested by subject
	}
}

/*
** fill our rooms names and type with 0 then fill our links with 0
*/

void	init_rooms(ANTS, ROOMS)
{
	t_xy	i;
	int		tmp_links[ants->max.y][ants->max.x];

	i.y = 0;
	while (i.y < ants->max.y)
	{
		while (i.x < ants->max.x)
		{
			NAME = "\0";
			TYPE = 0;
			rooms[i.y][i.x]->links = &tmp_links[i.y][i.x];; 
			init_links(ants, i, rooms, rooms->links)
			++i.x;
		}
		++i.y;
	}
}

void	init_links(t_ants *ants, t_xy pos, ROOMS, *LINKS)
{
	t_xy	i;

	i.y = 0;
	while (i.y < max.y)
	{
		while (i.x < max.x)
		{
			rooms[pos.y][pos.x]->links[i.y][i.x] = 0;
			++i.x;
		}
		++i.y;
	}
}

/*
** checks that comment is well formated. if it was the start (start == 2)
** it means that we now have to parse intermediate rooms
*/

int		not_comment(char *line, int *start)
{
	if (!ft_strcmp(line, "##start") && (*start++ == 1))
		return (0);
	else if (!ft_strcmp(line, "##end") && (*start++ == 4))
		return (0);
	else if (line[0] == '#')
	{
		if (*start == 2)
			++*start;
		return (0);
	}
	return (1);
}

/*
** function to check room string is sent as NAME X Y
** then add information relative to a new room
*/

int		add_room(ANTS, char *s, int type, *ROOMS)
{
	size_t	i;
	size_t	sp;

	sp = 0;
	i = 0;
	while (s[i])
		if (s[i++] == ' ')
			++sp;
	if (sp != 2)
		lem_in_error("Error : room format needs to be NAME X Y", &ants->loop);
	i = 0;
	while (s[i] != ' ')
		++i;
	ft_strncpy(ants->tmp_s1, s, i);
	while (i--)
		*s++; 
	i.x = ft_atoi(ft_strchr(s, ' ') + 1);
	i.y = ft_atoi(ft_strrchr(s, ' ') + 1);
	if (i.x < 0 || i.y < 0)
		lem_in_error("Error : Wrong format, negative (x, y)", &ants->loop);
	if (!NAME && !already_contain_name(ants, rooms))
		NAME = ants->tmp_s1;
	else
		lem_in_error("Error : Room already existed", &ants->loop);
	TYPE = type;
}

/*
** make sure that there is no room with the same name already existing
*/

int		already_contain_name(ANTS, ROOMS)
{
	t_xy	i;

	i.y = 0;
	while (i.y < max.y)
	{
		while (i.x < max.x)
		{
			if (!ft_strcmp(NAME, ants->tmp_s1))
				return (0);
			++i.x;
		}
		++i.y;
	}
	return (1);
}

/*
** parse links between rooms
*/

void 	parse_links(t_ants *ants, char *s)
{
	size_t	i;
	int		link;

	link = 0;
	i = 0;
	while (s[i])
		if (s[i++] == '-')
			++link;
	if (link != 1)
		lem_in_error("Error : Wrong room linkage format", &ants->loop);
	i = 0;
	while (s[i] != '-')
		++i;
	ants->tmp_s1 = ft_strncpy(room->name, s, i);
	while (i--)
		++*s; 
	while (s[i] != '-')
		++i;
	ants->tmp_s2-> = ft_strncpy(room->name, s, i);
	if (!check_room_name_and_link(ants, rooms, links))
		lem_in_error("Error : Invalid link", &ants->loop);
}

/*
** checks that room name matches with existing rooms and then link them
** also checks that it not a final room with if (TYPE == 3)
*/

int 	check_room_name_and_link(ANTS, ROOMS, LINKS)
{
	t_xy	i;

	i.y = 0;
	while (i.y < max.y)
	{
		while (i.x < max.x)
		{
			if (!ft_strcmp(NAME, ants->tmp_s1))
			{
				if (TYPE == 3)
					return (0);
				else
					return (link_to_other_room(i, ants, rooms, links));
			}
			++i.x;
		}
		++i.y;
	}
	return (0);
}

/*
** checks that room name matches with another existing room and then link them
** also checks that it not a starting room with if (TYPE == 1)
*/

int 	link_to_other_room(t_xy pos, ANTS, ROOMS, LINKS)
{
	t_xy	i;

	i.y = 0;
	while (i.y < max.y)
	{
		while (i.x < max.x)
		{
			if (!ft_strcmp(NAME, ants->tmp_s2))
			{
				if (TYPE == 1)
					return (0);
				else
				{
					room[pos.y][pos.x]->links[i.y][i.x] = 1;
					return (1);
				}
			}
			++i.x;
		}
		++i.y;
	}
	return (0);
}

/*
** function to return error
*/

void	lem_in_error(char *s, int *loop)
{
	//lem_in_free_line()
	ft_putendl_fd(s, 2);
	*loop = 0;
}

/*
** mlx functions
*/

#include "mlx.h"

/*
** function sleeps while awaiting user inputs
*/

void	hook_exposure(t_ants *e)
{
	mlx_hook(e->mlx->win, KEYPRESS, KEYPRESSMASK, hook, e);
	mlx_hook(e->mlx->win, KEYRELEASE, KEYRELEASEMASK, hook_move, e);
	mlx_loop_hook(e->mlx->mlx, draw_ants, e);
	mlx_loop(e->mlx->mlx);
}

/*
** 82 and 29 are 0, to reset. 53 is ESC
*/

int		hook(int k, t_ants *e)
{
	hook_move(k, e);
	if (k == 82 || k == 29)
		ft_init(e);
	if (k == 53)
		exit(1);
	return (0);
}

int		hook_move(int k, t_ants *e)
{
	if (k == K_A || k == K_LEFT)
		e->padding = 0 | LEFT;
	else if (k == K_D || k == K_RIGHT)
		e->padding = 0 | RIGHT;
	else if (k == K_S || k == K_DOWN)
		e->padding = 0 | DOWN;
	else if (k == K_W || k == K_UP)
		e->padding = 0 | UP;
	return (0);
}

int		draw_ants(t_ants *e)
{
	mlx_destroy_image(e->mlx->mlx, e->mlx->img);
	e->mlx->img = mlx_new_image(e->mlx->mlx, WIDTH, HEIGHT);
//	move(e);
	draw_rooms(e);
	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->mlx->img, 0, 0);
	return (0);
}

/*
** function to draw each room
*/

void	draw_rooms(ANTS, ROOMS)
{
	t_xy	i;

	ants->cell_dim.y = HEIGHT / (ants->max.y + 3); 
	ants->cell_dim.x = WIDTH / (ants->max.y + 3);
	i.y = 0;
	while (i.y < max.y)
	{
		while (i.x < max.x)
		{
			if (TYPE)
				draw_room(i, ants, rooms, TYPE);
			++i.x;
		}
		++i.y;
	}
}

/*
** function to draw the room
*/

void	draw_room(t_xy pos, ANTS, ROOMS)
{
	t_xy	i;

	i.y = ants->cell_dim.y * (pos.y + 2);
	while (i.y < ants->cell_dim.y * (pos.y + 3))
	{
		i.x = ants->cell_dim.x * (pos.x + 2);
		while (i.x < ants->cell_dim.x * (pos.x + 3))
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
