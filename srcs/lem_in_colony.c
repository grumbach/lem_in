/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_colony.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 14:01:56 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/18 19:53:59 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		set_em_names(char **par, void *names, const t_lemsize *size)
{
	int			namecount;
	int			i;
	char		(*name)[SIZEROOM][SIZENAME];

	name = names;
	namecount = 0;
	while (**par && !(i = 0))
		if (**par == '\n')
			(*par)++;
		else if (**par == '#')
			while (**par && **par != '\n')
				(*par)++;
		else if (ft_strchr(*par, '\n') < ft_strchr(*par, '-') && **par != ' ')
		{
			while (**par && **par != '\n' && **par != ' ' \
				&& ((*name)[namecount][i++] = **par))
				(*par)++;
			namecount++;
			while (**par != '\n' && **par)
				(*par)++;
		}
		else//carefull if ft_strchr(*par + i, '-') == NULL
			break ;
	return (namecount);
}

static int		set_em_links(char **par, void *names, void *links, \
				const t_lemsize *size)
{
	int			linkcount;
	int			(*link)[SIZEROOM][SIZELINK];
	char		(*name)[SIZEROOM][SIZENAME];

	name = names;
	link = links;
	linkcount = 0;
	ft_printf("(%c=%c)\n", **par, *++*par);
	return (linkcount);
}

static void		link_all_that(void *rooms, void *names, void *links, \
				const t_lemsize *size)
{
	t_rooms		(*room)[SIZEROOM];
	char		(*name)[SIZEROOM][SIZENAME];
	int			(*link)[SIZEROOM][SIZELINK];

	room = rooms;
	name = names;
	link = links;
}

static int		initialize_em(char **par, const t_lemsize *size)
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
	while (ft_isdigit(**par))
		(*par)++;
	return (1);
}

void			lem_set_colony(t_array *parse, const t_lemsize *size)
{
	t_rooms		rooms[SIZEROOM];
	char		names[SIZEROOM][SIZENAME];
	int			links[SIZEROOM][SIZELINK];
	char		*par;

	ft_bzero(&rooms, sizeof(rooms));
	ft_bzero(&names, sizeof(names));
	ft_bzero(&links, sizeof(links));
	par = LEM;
	if (!initialize_em(&par, size))
		LERROR(3, "ERROR -- This colony is sad and empty...");
	if (!ft_strstr(par, "\n##start\n"))
		LERROR(3, "ERROR -- Where should I ##start...");
	if (!ft_strstr(par, "\n##end\n"))
		LERROR(3, "ERROR -- Where is the ##end... My only friend...");
	if (!set_em_names(&par, names, size))
		LERROR(3, "ERROR -- Here's room 404 for you...");
	if (!set_em_links(&par, names, links, size))
		LERROR(3, "ERROR -- Zelda died : Link not found...");
	link_all_that(rooms, names, links, size);
}
