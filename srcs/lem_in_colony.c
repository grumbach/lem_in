/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_colony.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 14:01:56 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/20 10:29:15 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		set_em_names(char **par, void *names, const t_lemsize *size)
{
	int			namecount;
	int			i;
	char		(*name)[size->rooms + 1][size->maxname + 1];

	name = names;
	namecount = 0;
	while (!(i = 0) && **par)
		if (**par == '\n')
			(*par)++;
		else if (**par == '#')
			while (**par && **par != '\n')
				(*par)++;
		else if (ft_strchr(*par, '\n') < lem_check_link(*par) && **par != ' ')
		{
			while (**par && **par != '\n' && **par != ' ' \
				&& ((*name)[namecount][i++] = **par))
				(*par)++;
			namecount++;
			while (**par != '\n' && **par)
				(*par)++;
		}
		else
			break ;
	return (ft_strchr(*par, '-') ? namecount : -1);
}

static int		set_em_links_write(char *par, void *names, void *links, \
				const t_lemsize *size)
{
	int			i;
	int			pre;
	int			pos;
	int			(*link)[size->rooms + 1][size->maxlinks + 1];
	char		*bond;

	link = links;
	bond = ft_strchr(par, '-');
	pre = lem_find_name(par, names, bond - par, size);
	pos = lem_find_name(bond + 1, names, ft_strchr(par, '\n') - bond - 1, size);
	if (pre == -1 || pos == -1)
		return (0);
	i = 0;
	while ((*link)[pre][i] != -1)
		i++;
	(*link)[pre][i] = pos;
	i = 0;
	while ((*link)[pos][i] != -1)
		i++;
	(*link)[pos][i] = pre;
	return (1);
}

static int		set_em_links(char **par, void *names, void *links, \
				const t_lemsize *size)
{
	int			linkcount;
	int			(*link)[size->rooms + 1][size->maxlinks + 1];
	char		(*name)[size->rooms + 1][size->maxname + 1];

	name = names;
	link = links;
	linkcount = 0;
	while (**par)
		if (**par == '\n')
			(*par)++;
		else if (**par == '#')
			while (**par && **par != '\n')
				(*par)++;
		else
		{
			if (set_em_links_write(*par, names, links, size))
				linkcount++;
			while (**par != '\n' && **par)
				(*par)++;
		}
	return (linkcount);
}

static void		link_all_that(void *rooms, void *names, void *links, \
			const t_lemsize *size)
{
	t_rooms		(*room)[size->rooms + 1];
	char		(*name)[size->rooms + 1][size->maxname + 1];
	int			(*link)[size->rooms + 1][size->maxlinks + 1];
	int			i;

	room = rooms;
	name = names;
	link = links;
	i = 0;
	while (i < size->rooms + 1)
	{
		(*room)[i].roomname = &((*name)[i][0]);
		(*room)[i].links = &((*link)[i][0]);
		i++;
	}
}

void			lem_set_colony(t_array *parse, const t_lemsize *size)
{
	t_rooms		rooms[size->rooms + 1];
	char		names[size->rooms + 1][size->maxname + 1];
	int			links[size->rooms + 1][size->maxlinks + 1];
	char		*par;
	int			ret;

	ft_bzero(rooms, sizeof(rooms));
	ft_bzero(names, sizeof(names));
	ft_bzero(links, sizeof(links));
	par = LEM;
	if (!lem_initialize_em(links, &par, size))
		LERROR(3, "ERROR -- This colony is sad and empty...");
	if (!(ret = set_em_names(&par, names, size)))
		LERROR(3, "ERROR -- Here's room 404 for you...");
	if (ret == -1)
		LERROR(3, "ERROR -- Zelda died : Link not found...");
	if (!set_em_links(&par, names, links, size))
		LERROR(3, "ERROR -- Zelda died : Link not found...");
	if (!(ret = lem_start_end(LEM, rooms, names, size)))
		LERROR(3, "ERROR -- Where should I ##start...");
	if (ret == -1)
		LERROR(3, "ERROR -- Where is the ##end... My only friend...");
	link_all_that(rooms, names, links, size);
	lem_smart_ant(rooms, size);
}
