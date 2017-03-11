/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 14:01:56 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/11 16:02:48 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		lem_fill_rooms(t_array *parse, void *rooms, void *name, \
								void *links)
{
	(void)parse;
	(void)rooms;
	(void)name;
	(void)links;
	return (3);
}

void			lem_parser(t_array *parse, t_lemsize *size)
{
	t_rooms		rooms[size->rooms];
	char		name[size->rooms][size->maxname];
	int			links[size->rooms][size->maxlinks];
	int			ants;

	ft_bzero(&rooms, sizeof(rooms));
	ft_bzero(&name, sizeof(name));
	ft_bzero(&links, sizeof(links));
	ants = lem_fill_rooms(parse, rooms, name, links);
}
