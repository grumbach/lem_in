/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_solver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 03:49:36 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/31 10:43:03 by agrumbac         ###   ########.fr       */
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

void			lem_smart_ant(void *rooms, t_lemsize *size)
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
	lem_pathfinder(maxflux, rooms, size);
}
