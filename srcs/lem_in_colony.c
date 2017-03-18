/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_colony.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 14:01:56 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/18 16:54:36 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				set_em_names(char **par, void *names, const t_lemsize *size)
{
	int			namecount;
	char		(*name)[size->rooms][size->maxname];

	name = names;
	namecount = 0;

	ft_printf("(%c+%c)\n", **par, *++*par);

	if (!namecount)
		return (0);
	return (1);
}

int				set_em_links(char **par, void *names, void *links, \
				const t_lemsize *size)
{
	int			linkcount;
	int			(*link)[size->rooms][size->maxlinks];
	char		(*name)[size->rooms][size->maxname];

	name = names;
	link = links;
	linkcount = 0;

	ft_printf("(%c=%c)\n", **par, *++*par);

	if (!linkcount)
		return (0);
	return (1);
}

void			link_all_that(void *rooms, void *names, void *links, \
				const t_lemsize *size)
{
	t_rooms		(*room)[size->rooms];
	char		(*name)[size->rooms][size->maxname];
	int			(*link)[size->rooms][size->maxlinks];

	room = rooms;
	name = names;
	link = links;
}

int				initialize_em(char **par, const t_lemsize *size)
{
	if (size->ants <= 0)
		return (0);
	while (**par == '#')
	{
		while (*++*par && **par != '\n')
			;
		if (**par == '\n')
			(*par)++;
	}
	while (ft_isdigit(**par) && **par++)
		;
	return (1);
}

void			lem_set_colony(t_array *parse, const t_lemsize *size)
{
	t_rooms		rooms[size->rooms];
	char		names[size->rooms][size->maxname];
	int			links[size->rooms][size->maxlinks];
	char		*par;

	ft_bzero(&rooms, sizeof(rooms));
	ft_bzero(&names, sizeof(names));
	ft_bzero(&links, sizeof(links));
	par = LEM;
	if (!initialize_em(&par, size))
		LERROR(3, "ERROR -- This colony is sad and empty...");
	if (!ft_strstr(par, "\n##start\n"))
		LERROR(3, "ERROR -- You should ##start a carreer in Wordpress...");
	if (!ft_strstr(par, "\n##end\n"))
		LERROR(3, "ERROR -- There's no ##end to your stupidity...");
	if (!set_em_names(&par, names, size))
		LERROR(3, "ERROR -- No room for you in my heart...");
	if (!set_em_links(&par, names, links, size))
		LERROR(3, "ERROR -- Get a link...");
	link_all_that(rooms, names, links, size);
}
