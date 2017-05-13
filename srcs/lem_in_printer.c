/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 18:44:28 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/13 15:47:45 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		print_ants_moves(const void *pathlens, \
				const void *pathlists, void *rooms, const t_lemsize *size)
{
	const int	(*pathlist)[size->maxflux][size->rooms + 1];
	const int	(*pathlen)[size->maxflux];
	int			a_e[4];
	const char	*color[6] = {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN};

	t_rooms(*room)[size->rooms + 1];
	a_e[1] = lem_end(rooms, size);
	pathlist = pathlists;
	room = rooms;
	pathlen = pathlens;
	while ((a_e[0] = (*room)[a_e[1]].ants) != size->ants && \
	(a_e[3] = -1))
		while (++a_e[3] < size->maxflux &&
		(a_e[2] = (*pathlen)[a_e[3]] ? (*pathlen)[a_e[3]] + 1 : 0) && \
		ft_printf("\n"))
			while (a_e[2]--)
				if ((*pathlist)[a_e[3]][a_e[2]] != a_e[1] && \
				(*pathlist)[a_e[3]][a_e[2]] != -1 && \
				(*room)[(*pathlist)[a_e[3]][a_e[2]]].ants && ++a_e[0])
				{
					(*room)[(*pathlist)[a_e[3]][a_e[2]]].ants--;
					(*room)[(*pathlist)[a_e[3]][a_e[2] + 1]].ants++;
					ft_printf("L%s%d-%s ""\e[0m", color[a_e[0] % 6], a_e[0],
					(*room)[(*pathlist)[a_e[3]][a_e[2] + 1]].roomname);
				}
}

void			lem_print_answ(const void *pathlens, \
				const void *pathlists, void *rooms, const t_lemsize *size)
{
	t_rooms(*room)[size->rooms + 1];
	room = rooms;
	ft_printf("%s", size->par);
	(*room)[lem_start(rooms, size)].ants = size->ants;
	print_ants_moves(pathlens, pathlists, rooms, size);
	ft_printf("\n");
}
