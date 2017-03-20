/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_pathfinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 13:49:16 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/20 13:56:46 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		lem_pathfinder(const int maxflux, const void *rooms, \
				const t_lemsize *size)
{
	int		pathlist[maxflux][size->rooms + 1];

	ft_bzero(pathlist, sizeof(pathlist));
	(void)rooms;
}
