/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 18:44:28 by agrumbac          #+#    #+#             */
/*   Updated: 2017/04/09 19:23:49 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void                   lem_print_answ(const t_xy pathlen, void *pathlists, \
	void *rooms, const t_lemsize *size)
	{
		t_rooms         (*room)[size->rooms + 1];
		int                     (*pathlist)[size->maxflux][size->rooms + 1];
		int                     ants;
		int                     i;

		pathlist = pathlists;
		room = rooms;
		ants = size->ants;
		ft_printf("%s\n", size->par);




		//shortest path
		for (int i = 0; i <= pathlen.x; i++)
		ft_printf("%s[%d]->", (*room)[(*pathlist)[0][i]].roomname, \
		(*pathlist)[0][i]);
		ft_printf("\n\n");



		int             path;
		int             used_paths = 1;

		while (--ants + 1)
		{
			path = -1;
			while (++path < used_paths)
			{
				i = -1;
				while ((*pathlist)[path][++i] != -1)
				{
					//    ft_printf("=%d=%d=", i, (*pathlist)[path][i]);
					ft_printf("L%d-%s", size->ants - ants, (*room)[(*pathlist)[path][i]].roomname);
					ft_printf("\n");
				}
			}
		}
	}











// for (int i = 0; i < size->rooms; i++)
//      ft_printf("==%s[%d]\n", (*room)[i].roomname, (*room)[i].depth);
// ft_printf("Pathlen = %d\n", pathlen);
// ft_printf("\n");
// for (int i = 0; i <= pathlen.y; i++)
//      ft_printf("%s[%d]->", (*room)[(*pathlist)[0][i]].roomname, \
//              (*pathlist)[0][i]);
// ft_printf("\n");
