/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_pathfinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 13:49:16 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/31 17:28:29 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	set_depths(const t_lemsize *size, t_rooms rooms[size->rooms + 1], \
				const int depth, const int where)
{
	int		i;

	i = 0;
	if (where == lem_start(rooms, size))
		return ;
	rooms[where].depth = depth ? depth : -1;
	while (rooms[where].links[i] != -1)
	{
		if (rooms[rooms[where].links[i]].depth > depth + 1 || \
			!rooms[rooms[where].links[i]].depth)
			set_depths(size, rooms, depth + 1, rooms[where].links[i]);
		++i;
	}
}

void		lem_pathfinder(void *rooms, const t_lemsize *size)
{
	int		pathlist[size->maxflux][size->rooms + 1];

	set_depths(size, rooms, 0, lem_end(rooms, size));
	(void)pathlist;
}
