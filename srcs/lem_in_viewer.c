/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_viewer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 00:56:57 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/12 08:53:21 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in_viewer.h"
#include "mlx.h"


static int		hook_move(int k, t_env *e)
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

/*
** 82 and 29 are 0, to reset. 53 is ESC
*/

static int		hook(int k, t_env *e)
{
	hook_move(k, e);
	if (k == 82 || k == 29)
		ft_init(e);
	if (k == 53)
		exit(1);
	return (0);
}

static int		ants(t_env *e)
{
	mlx_destroy_image(e->mlx->mlx, e->mlx->img);
	e->mlx->img = mlx_new_image(e->mlx->mlx, WIDTH, HEIGHT);
	move(e);
	draw(e);
	mlx_put_image_to_window(e->mlx->mlx, e->mlx->win, e->mlx->img, 0, 0);
	return (0);
}

static void	hook_exposure(t_env *e)
{
	mlx_hook(e->mlx->win, KEYPRESS, KEYPRESSMASK, hook, e);
	mlx_hook(e->mlx->win, KEYRELEASE, KEYRELEASEMASK, hook_move, e);
	mlx_loop_hook(e->mlx->mlx, ants, e);
	mlx_loop(e->mlx->mlx);
}

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
** fill our rooms names and type with 0 then fill our links with 0
*/

void	init_rooms(t_ants *ants, *ROOMS)
{
	t_xy	i;
	t_rooms	tmp_links[ants->max.y][ants->max.x];

	rooms->links = &tmp_links; 
	i.y = 0;
	while (i.y < max.y)
	{
		while (i.x < max.x)
		{
			NAME = "\0";
			TYPE = 0;
			init_links(ants, i, rooms, rooms->links)
			++i.x;
		}
		++i.y;
	}
}

void	init_links(t_ants *ants, t_xy pos, *ROOMS, *LINKS)
{
	t_xy	i;

	i.y = 0;
	while (i.y < max.y)
	{
		while (i.x < max.x)
		{
			room[pos.y][pos.x]->links[i.y][i.x] = 0;
			++i.x;
		}
		++i.y;
	}
}

/*
** variable start is to check the position inside the parser
** while start = 0 we parse nb is the nb of ants
** while start = 1 we look for ##start
** while start is between 2 and 4 we parse rooms,
** while start = 5 we parse links
*/

void	lem_in_parsing(t_ants *ants)
{
	char	*line;
	int		start;
	t_rooms	rooms[ants->max.y][ants->max.x]

	start = 0;
	ants->loop = 1;
	init_rooms(ants, &rooms);
	while (ft_get_next_line(0, &line) > 0 && ants->loop)
	{
		if (not_comment(line, &start))
		{
			if (start == 0 && ++start)
				ants->nb = ft_atoi(line);
			else if (start < 5)
				add_room(ants, line, start - 1, &rooms);
			else if (start > 4)
				parse_links(ants, line);
		}
		else if (!not_comment(line, &start))
			;// we need to store the comment as requested by subject
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
** UNFINISHED function to graphically display ants
*/

int	create_fdf(t_ants ants, map_dim[])
{
	while (++i.y < f-)
	{
		get_next_line(0, &line);
		i.x = -1;
		while (++i.x < f->piece_dim.x)
			p[i.y][i.x] = INT2(line[i.x]);
	}
	return (0);
}
