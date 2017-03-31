/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_pathfinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 13:49:16 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/31 10:55:20 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
//
// static void	clear_pathlist(void *pathlists, void *rooms, \
// 				const t_lemsize *size)
// {
// 	int			(*pathlist)[size->maxflux][size->rooms + 1];
// 	int			i;
// 	int			j;
//
// 	pathlist = pathlists;
// 	i = -1;
// 	while (++i < size->maxflux)
// 	{
// 		j = -1;
// 		while (++j < size->rooms + 1)
// 			if (j)
// 				(*pathlist)[i][j] = -1;
// 			else
// 				(*pathlist)[0][0] = lem_start(rooms, size);
// 	}
// }
//
// static void	print_solution(const void *pathlists, const t_lemsize *size)
// {}
//
// static int	solution_len(void *pathlists, const t_lemsize *size)
// {}
//
// static int	path_finder(t_xy move, void *pathlists, void *rooms, \
// 				const t_lemsize *size)
// {}
//
// static int	path(const int solution, void *pathlists, void *rooms, \
// 				const t_lemsize *size)
// {
// 	int			(*pathlist)[size->maxflux][size->rooms + 1];
// 	t_rooms		(*room)[size->rooms + 1];
// 	t_xy		move;
// 	int			link;
//
// 	pathlist = pathlists;
// 	room = rooms;
// 	move = (t_xy){0, 1};
// 	link = 0;
// 	if ()
// 		return (-1);
// 	if ()
// 		return (solution_len(pathlist, size));
// 	(*pathlist)[move.y][move.x] = ;
// 	if (path_finder(move, pathlists, rooms, size) == -1)
// 	{
// 		(*pathlist)[move.y][move.x] = -1;
// 	}
// }

void		lem_pathfinder(const int maxflux, void *rooms, \
				const t_lemsize *size)
{
	(void)maxflux;
	(void)size;
	t_rooms		(*room)[size->rooms + 1];

	room = rooms;
	ft_printf("start : %s, end : %s\n", \
		(*room)[lem_start(rooms, size)].roomname, \
		(*room)[lem_end(rooms, size)].roomname);
	// int		pathlist[maxflux][size->rooms + 1];
	// int		solution;
	// int		bestsol;
	// int		bestlen;
	// int		tmpsol;
	//
	// solution = 1;
	// bestsol = -1;
	// bestlen = 2147483647;
	// while (tmpsol != -1)
	// {
	// 	clear_pathlist(pathlist, rooms, sizeof(pathlist));
	// 	tmpsol = path(solution, pathlist, rooms, size);
	// 	if (tmpsol > 0 && tmpsol < bestlen)
	// 	{
	// 		bestlen = tmpsol;
	// 		bestsol = solution;
	// 	}
	// 	solution++;
	// }
	// clear_pathlist(pathlist, rooms, sizeof(pathlist));
	// path(bestsol, pathlist, rooms, size);
	// print_solution(pathlist, size);
}
