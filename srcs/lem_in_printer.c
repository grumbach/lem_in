/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 18:44:28 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/12 13:54:16 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_ants_moves(const void *pathlens, \
				const void *pathlists, void *rooms, const t_lemsize *size)
{
	t_rooms		(*room)[size->rooms + 1];
	const int	(*pathlist)[size->maxflux][size->rooms + 1];
	const int	(*pathlen)[size->maxflux];
	t_xy		explore;
	int			ant_nb;
	const int	end = lem_end(rooms, size);
	const char	*color[6] = {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN};

	pathlist = pathlists;
	room = rooms;
	pathlen = pathlens;
	while ((ant_nb = (*room)[end].ants) != size->ants && (explore.y = -1))//while not all ants in end
		while (++explore.y < size->maxflux &&
		(explore.x = (*pathlen)[explore.y] ? (*pathlen)[explore.y] + 1 : 0) && \
		ft_printf("\n"))//all path from 1st
			while (explore.x--)//all rooms from last (closest to end)
				if ((*pathlist)[explore.y][explore.x] != end && \
				(*pathlist)[explore.y][explore.x] != -1 && \
				(*room)[(*pathlist)[explore.y][explore.x]].ants && ++ant_nb)//if in a path && there is ant here
				{
					(*room)[(*pathlist)[explore.y][explore.x]].ants--;
					(*room)[(*pathlist)[explore.y][explore.x + 1]].ants++;
					ft_printf("L%s%d-%s ""\e[0m", color[ant_nb % 6], ant_nb, \
					(*room)[(*pathlist)[explore.y][explore.x + 1]].roomname);
				}//move ants towards end
}

void			lem_print_answ(const void *pathlens, \
				const void *pathlists, void *rooms, const t_lemsize *size)
{
	t_rooms					(*room)[size->rooms + 1];

	room = rooms;
	ft_printf("%s", size->par);
	(*room)[lem_start(rooms, size)].ants = size->ants;
	print_ants_moves(pathlens, pathlists, rooms, size);
	ft_printf("\n");
}
