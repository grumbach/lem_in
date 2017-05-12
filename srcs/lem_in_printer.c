/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 18:44:28 by agrumbac          #+#    #+#             */
/*   Updated: 2017/05/12 12:01:39 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void                   lem_print_answ(const void *pathlens, \
		const void *pathlists, void *rooms, const t_lemsize *size)
{
	t_rooms					(*room)[size->rooms + 1];
	const int				(*pathlist)[size->maxflux][size->rooms + 1];
	const int				(*pathlen)[size->maxflux];
	t_xy					explore;
	int						ant_nb;
	int						end;

	// ANT nb FIX TODO
	pathlist = pathlists;
	room = rooms;
	pathlen = pathlens;
	ft_printf("%s\n", size->par);
	explore = (t_xy){-1, -1};
	end = lem_end(rooms, size);
	(*room)[lem_start(rooms, size)].ants = size->ants;
	while ((ant_nb = (*room)[end].ants) != size->ants && (explore.y = -1))//while not all ants in end
	{
		while (++explore.y < size->maxflux && ++ant_nb && \
			(explore.x = (*pathlen)[explore.y] + 1))//all path from 1st
		{
			// ft_printf("hi");
			while (explore.x--)//all rooms from last (closest to end)
			{
				// ft_printf("y%d, x%d : %s\n", explore.y, explore.x, 0);//
				if ((*pathlist)[explore.y][explore.x] != end && \
				(*pathlist)[explore.y][explore.x] != -1 && \
				(*room)[	(*pathlist)[explore.y][explore.x]	].ants)//if in a path && there is ant here
				{
					(*room)[	(*pathlist)[explore.y][explore.x]	].ants--;
					(*room)[	(*pathlist)[explore.y][explore.x + 1]	].ants++;
					ft_printf("L%d-%s ", ant_nb, (*room)[(*pathlist)[explore.y][explore.x + 1]].roomname);
					ant_nb++;
				}//move ants towards end
			}
		ft_printf("\n");//end of one turn
		}
	}

	//
	// //show all paths NOTE
	// for (int l = 0; l < size->maxflux; l++){
	// 	for (int j = 0; j < size->rooms + 1; j++){
	// 		ft_printf("[%d]->", (*pathlist)[l][j]);}
	// 	ft_printf("\n");}
	// //

	//shortest path
	// for (int i = 0; i <= pathlen.x; i++)
	// ft_printf("%s[%d]->", (*room)[(*pathlist)[0][i]].roomname, \
	// (*pathlist)[0][i]);
	// ft_printf("\n\n");

	//
	// int             path;
	// int             used_paths = 1;
	//
	// while (--ants + 1)
	// {
	// 	path = -1;
	// 	while (++path < used_paths)
	// 	{
	// 		i = -1;
	// 		while ((*pathlist)[path][++i] != -1)
	// 		{
	// 			//    ft_printf("=%d=%d=", i, (*pathlist)[path][i]);
	// 			ft_printf("L%d-%s", size->ants - ants, (*room)[(*pathlist)[path][i]].roomname);
	// 			ft_printf("\n");
	// 		}
	// 	}
	// }
	//
	//
	// for (int i = 0; i < size->rooms; i++)
	//      ft_printf("==%s[%d]\n", (*room)[i].roomname, (*room)[i].depth);
	// ft_printf("Pathlen = %d\n", pathlen);
	// ft_printf("\n");
	// for (int i = 0; i <= pathlen.y; i++)
	//      ft_printf("%s[%d]->", (*room)[(*pathlist)[0][i]].roomname, \
	//              (*pathlist)[0][i]);
	// ft_printf("\n");

	// for (int i = 0; i < size->rooms + 1; i++) {
	// 	ft_printf("[%d]-", (*pathlist)[0][i]);
	// }
	// ft_printf("\n");
}
