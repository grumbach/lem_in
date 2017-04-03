/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_pathfinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 13:49:16 by agrumbac          #+#    #+#             */
/*   Updated: 2017/04/03 17:48:18 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	set_depths(const int depth, const int where, void *rooms, \
				const t_lemsize *size)
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
			set_depths(depth + 1, (*room)[where].links[i], rooms, size);
		++i;
	}
}

static int	find_path(t_path *path, const int where, const int pathlen)
{
	int		(*pathlist)[path->size->maxflux][path->size->rooms + 1];
	t_rooms (*room)[path->size->rooms + 1];
	int		min;
	int		minlen;
	int		i;

	pathlist = path->pathlists;
	room = path->rooms;
	min = INT_MAX;
	minlen = INT_MAX;
	(*pathlist)[0][pathlen] = where;
	if (where == lem_end(path->rooms, path->size))
		return (pathlen);
	i = -1;
	while ((*room)[where].links[++i] != -1)
		if ((*room)[(*room)[where].links[i]].depth)
			min = MIN(min, (*room)[(*room)[where].links[i]].depth);
	i = -1;
	while ((*room)[where].links[++i] != -1)
		if ((*room)[(*room)[where].links[i]].depth == min)
			minlen = MIN(minlen, \
				find_path(path, (*room)[where].links[i], pathlen + 1));
	return (minlen);
}

int			lem_pathfinder(void *rooms, const t_lemsize *size)
{
	int		pathlists[size->maxflux][size->rooms + 1];
	t_path	path;
	int		pathlen;

	ft_bzero(&path, sizeof(path));
	ft_bzero(&pathlists, sizeof(pathlists));
	set_depths(0, lem_end(rooms, size), rooms, size);
	path.rooms = rooms;
	path.pathlists = pathlists;
	path.size = size;
	pathlen = find_path(&path, lem_start(rooms, size), 0);
	if (pathlen == INT_MAX)
		return (0);
	lem_print_answ((t_xy){pathlen, 1}, pathlists, rooms, size);
	return (1);
}
