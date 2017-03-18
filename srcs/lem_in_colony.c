/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_colony.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 14:01:56 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/18 23:54:06 by agrumbac         ###   ########.fr       */
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
	while (!(i = 0) && **par)
		if (**par == '\n')
			(*par)++;
		else if (**par == '#')
			while (**par && **par != '\n')
				(*par)++;
		else if (ft_strchr(*par, '\n') < ft_strchr(*par, '-') && **par != ' ')
		{
			// ft_printf("par{%s} = ", *par);
			while (**par && **par != '\n' && **par != ' ' \
				&& ((*name)[namecount][i++] = **par))
				(*par)++;
			(*name)[4][0] = 'T';(*name)[4][1] = 'O';
			ft_printf("*%s*\n", (*name)[4]);
			namecount++;
			while (**par != '\n' && **par)
				(*par)++;
		}
		else//carefull if ft_strchr(*par + i, '-') == NULL
			break ;

	// for (int rr = 0; rr < namecount; rr++)
	// {
	// 	ft_printf("*%s*\n", (char*)&(name[rr][0]));
	// }

	return (namecount);
}

static int		set_em_links(char **par, void *names, void *links, \
				const t_lemsize *size)
{
	int			linkcount_i[2];
	t_xy		friends;
	char		*bond;
	int			(*link)[SIZEROOM][SIZELINK];
	char		(*name)[SIZEROOM][SIZENAME];

	name = names;
	link = links;
	ft_bzero(&linkcount_i, sizeof(linkcount_i));
	while (**par)
		if (**par == '\n')
			(*par)++;
		else if (**par == '#')
			while (**par && **par != '\n')
				(*par)++;
		else if ((bond = ft_strchr(*par, '-')))
		{
			if ((friends.x = lem_find_name(*par, names, bond - *par, size) > 0))
				if ((friends.y = lem_find_name(bond + 1, names, \
					 ft_strchr(*par, '\n') - bond - 1, size) > 0))
				{
					 while ((*link)[friends.x][linkcount_i[1]] > -1)
						linkcount_i[1]++;
					linkcount_i[1] = 0;
					(*link)[friends.x][linkcount_i[1]] = friends.y;
					while ((*link)[friends.y][linkcount_i[1]] > -1)
						linkcount_i[1]++;
					(*link)[friends.y][linkcount_i[1]] = friends.x;
				}
			while (**par != '\n' && **par)
				(*par)++;
		}
	return (linkcount_i[0]);
}

static void		link_all_that(void *rooms, void *names, void *links, \
				const t_lemsize *size)
{
	t_rooms		(*room)[SIZEROOM];
	char		(*name)[SIZEROOM][SIZENAME];
	int			(*link)[SIZEROOM][SIZELINK];
	int			i;

	room = rooms;
	name = names;
	link = links;
	i = 0;
	while (i < SIZEROOM)
	{
		(*room)[i].roomname = &((*name)[i][0]);
		(*room)[i].links = &((*link)[i][0]);
		i++;
	}
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

	ft_bzero(rooms, sizeof(rooms));
	ft_bzero(names, sizeof(names));
	ft_bzero(links, sizeof(links));
	lem_reset_links(links, size);
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
