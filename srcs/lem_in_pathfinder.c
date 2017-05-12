/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_pathfinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 13:49:16 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/12 11:00:53 by agrumbac         ###   ########.fr       */
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

static int	find_paths(t_path *path, const int where, const t_xy pathref)
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
	(*pathlist)[pathref.y][pathref.x] = where;
	if (where == lem_end(path->rooms, path->size))
		return (pathref.x);
	i = -1;
	while ((*room)[where].links[++i] != -1)
		if ((*room)[(*room)[where].links[i]].depth)
			min = MIN(min, (*room)[(*room)[where].links[i]].depth);
	i = -1;
	while ((*room)[where].links[++i] != -1)
		if ((*room)[(*room)[where].links[i]].depth == min)
			minlen = MIN(minlen, \
				find_paths(path, (*room)[where].links[i], \
					(t_xy){pathref.x + 1, pathref.y}));
	return (minlen);
}

static void	clean_paths(const void *pathlens, void *pathlists, \
			const t_lemsize *size)
{
	int			(*pathlist)[size->maxflux][size->rooms + 1];
	const int	(*pathlen)[size->maxflux];
	t_xy		i;

	pathlist = pathlists;
	pathlen = pathlens;
	i.y = -1;
	while (++i.y < size->maxflux)
	{
		i.x = (*pathlen)[i.y] ? (*pathlen)[i.y] : -1;
		while (++i.x < size->rooms + 1)
			(*pathlist)[i.y][i.x] = -1;
	}
}

int			lem_pathfinder(void *rooms, const t_lemsize *size)
{
	int		pathlists[size->maxflux][size->rooms + 1];
	int		pathlens[size->maxflux];
	t_path	path;

	ft_bzero(&path, sizeof(path));
	ft_bzero(&pathlists, sizeof(pathlists));
	ft_bzero(&pathlens, sizeof(pathlens));
	set_depths(0, lem_end(rooms, size), rooms, size);
	path.rooms = rooms;
	path.pathlists = pathlists;
	path.size = size;
	path.pathlens = pathlens;
	pathlens[0] = find_paths(&path, lem_start(rooms, size), (t_xy){0, 0});
	if (pathlens[0] == INT_MAX)
		return (0);
	clean_paths(pathlens, pathlists, size);
	lem_print_answ(pathlens, pathlists, rooms, size);
	return (1);
}
