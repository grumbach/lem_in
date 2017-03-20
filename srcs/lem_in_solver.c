/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_solver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 03:49:36 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/20 11:22:05 by agrumbac         ###   ########.fr       */
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
		ft_printf("name[%s] ", (*room)[i].roomname);
		j = -1;
		ft_printf("ants[%d] type[%d] links", (*room)[i].ants, (*room)[i].type);
		while ((*room)[i].links[++j] != -1)
			ft_printf("[%s]", (*room)[(*room)[i].links[j]].roomname);
		i++;
		ft_printf("\n");
	}
}

void			lem_smart_ant(void *rooms, const t_lemsize *size)
{
	t_rooms(*room)[size->rooms + 1];
	room = rooms;
	if (size->gflag)
		print_colony(rooms, size);
}
