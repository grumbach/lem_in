/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_solver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 03:49:36 by agrumbac          #+#    #+#             */
/*   Updated: 2017/04/03 18:12:47 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_colony(void *rooms, const t_lemsize *size)
{
	int			i;
	int			j;

	t_rooms(*room)[size->rooms + 1];
	room = rooms;
	i = 0;
	ft_printf("%d %d %d %d %d %d %d\n", size->rooms, size->maxname, \
		size->maxlinks, size->min.x, size->max.x, size->min.y, size->max.y);
	while (i < size->rooms)
	{
		ft_printf("%s %d ", (*room)[i].roomname, (*room)[i].type);
		j = -1;
		while ((*room)[i].links[++j] != -1)
			ft_printf("[%d]", (*room)[i].links[j]);
		i++;
		ft_printf("\n");
	}
}

int				lem_start(void *rooms, const t_lemsize *size)
{
	int			i;

	t_rooms(*room)[size->rooms + 1];
	room = rooms;
	i = 0;
	while (!((*room)[i].type & START))
		i++;
	return (i);
}

int				lem_end(void *rooms, const t_lemsize *size)
{
	int			i;

	t_rooms(*room)[size->rooms + 1];
	room = rooms;
	i = 0;
	while (!((*room)[i].type & END))
		i++;
	return (i);
}

int				lem_smart_ant(void *rooms, t_lemsize *size)
{
	int			maxflux;
	int			i;

	t_rooms(*room)[size->rooms + 1];
	room = rooms;
	maxflux = 0;
	i = 0;
	if (size->gflag)
		print_colony(rooms, size);
	while ((*room)[lem_start(rooms, size)].links[i] != -1)
		i++;
	while ((*room)[lem_end(rooms, size)].links[maxflux] != -1)
		maxflux++;
	size->maxflux = MIN(maxflux, i);
	return (lem_pathfinder(rooms, size));
}

void			lem_print_answ(const t_xy pathlen, void *pathlists, \
					void *rooms, const t_lemsize *size)
{
	t_rooms		(*room)[size->rooms + 1];
	int			(*pathlist)[size->maxflux][size->rooms + 1];
	// t_xy		pa;
	// t_xy		old;
	int			ants;
	// int			i;

	pathlist = pathlists;
	room = rooms;
	ants = size->ants;
	ft_printf("%s\n", size->par);

	//shortest path
	for (int i = 0; i <= pathlen.x; i++)
		ft_printf("%s[%d]->", (*room)[(*pathlist)[0][i]].roomname, \
			(*pathlist)[0][i]);
	ft_printf("\n");
	//
	//
	//
	// while (ants)
	// {
	// 	i = 0;
	// 	pa.x = -1;
	// 	while (++pa.x < pathlen.x && (i = -1) && (pa.y = -1))
	// 	{
	// 		// while (pp)//move old ants
	// 		// 	if (ants % pa.y)
	// 		// 	{
	// 		// 		ft_printf("L%d-%s", i, (*room)[(*pathlist)[pa.y][pa.x]]);
	// 		// 		--ants;
	// 		// 	}
	// 		while (++pa.y < pathlen.y && ++i)//move new ants
	// 			if (ants % pa.y)
	// 			{
	// 				ft_printf("L%d-%s", i, (*room)[(*pathlist)[pa.y][pa.x]]);
	// 				--ants;
	// 			}
	// 	}
	// }
	// for (int i = 0; i < size->rooms; i++)
	// 	ft_printf("==%s[%d]\n", (*room)[i].roomname, (*room)[i].depth);
	// ft_printf("Pathlen = %d\n", pathlen);
	// ft_printf("\n");
	// for (int i = 0; i <= pathlen.y; i++)
	// 	ft_printf("%s[%d]->", (*room)[(*pathlist)[0][i]].roomname, \
	// 		(*pathlist)[0][i]);
	// ft_printf("\n");
}
