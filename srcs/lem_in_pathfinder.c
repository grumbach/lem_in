/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_pathfinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 13:49:16 by agrumbac          #+#    #+#             */
/*   Updated: 2017/04/03 07:54:00 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	set_depths(const t_lemsize *size, void *rooms, \
				const int depth, const int where)
{
	t_rooms (*room)[size->rooms + 1];
	int		i;

	room = rooms;
	i = 0;
	if (where == lem_start(rooms, size))
		return ;
	(*room)[where].depth = depth ? depth : -1;
	while ((*room)[where].links[i] != -1)
	{
		if ((*room)[(*room)[where].links[i]].depth > depth + 1 || \
			!(*room)[(*room)[where].links[i]].depth)
			set_depths(size, rooms, depth + 1, (*room)[where].links[i]);
		++i;
	}
}

void		lem_pathfinder(void *rooms, const t_lemsize *size)
{
	int		pathlist[size->maxflux][size->rooms + 1];

	set_depths(size, rooms, 0, lem_end(rooms, size));
	(void)pathlist;

	t_rooms (*room)[size->rooms + 1] = rooms;
	for (int i = 0; i < size->rooms; i++)
		ft_printf("[%s](%d)\n", (*room)[i].roomname, (*room)[i].depth);
}
