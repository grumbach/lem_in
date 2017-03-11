/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 14:01:56 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/11 18:58:13 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

///////////////////////////
int			n;

n = 0;
while (ft_isalnum(LEM[*i + n]) && LEM[*i + n] != '\n' && LEM[*i + n])
	n++;
size->maxname = size->maxname > n ? size->maxname : n;
if (LEM[*i + n] == '-' && (*i + n))
	(*ants_rooms_links)++;
*i += n;
if (*ants_rooms_links == 1)
{
	LEM[*i] == ' ' ? (*i)++ : errors(2, 0);
	if (!(ft_isdigit(LEM[*i]) && LEM[*i] != '\n' && LEM[*i]))
		errors(2, 0);
	while (ft_isdigit(LEM[*i]) && LEM[*i] != '\n' && LEM[*i])
		(*i)++;
	LEM[*i] == ' ' ? (*i)++ : errors(2, 0);
	if (!(ft_isdigit(LEM[*i]) && LEM[*i] != '\n' && LEM[*i]))
		errors(2, 0);
	while (ft_isdigit(LEM[*i]) && LEM[*i] != '\n' && LEM[*i])
		(*i)++;
	size->rooms += 1;
}
else
LEM[*i] == '-' ? (*i)++ : errors(2, 0);
if (!(ft_isalnum(LEM[*i]) && LEM[*i] != '\n' && LEM[*i]))
	errors(2, 0);
while (ft_isalnum(LEM[*i]) && LEM[*i] != '\n' && LEM[*i])
	(*i)++;
size->maxlinks += 1;
//////////////////////////

static int		lem_fill_name(t_lemsize *size, char *parse, void *name, int r)
{
	char		(*pname)[size->rooms][size->maxname];
	int			i;
	int			j;

	i = 0;
	j = 0;
	pname = name;
	while (ft_isalnum(parse[i]) && parse[i] != '\n' && parse[i])
	{
		pname[r][j] = parse[i];
		j++;
	}
	i++;
	while (ft_isdigit(parse[i]) && parse[i] != '\n' && parse[i])
		i++;
	i++;
	while (ft_isdigit(parse[i]) && parse[i] != '\n' && parse[i])
		i++;
	i++;
	return (i);
}

static int		lem_fill_links(t_lemsize *size, char *parse, void *links, \
								void *name)
{
	char		(*plinks)[size->rooms][size->maxlinks];
	char		(*pname)[size->rooms][size->maxname];
	char		tmp[size->maxname];
	int			i;
	int			j;

	i = 0;
	j = 0;
	plinks = links;
	pname = name;
	ft_bzero(&tmp, sizeof(tmp));
	// while (ft_isalnum(parse[i]) && parse[i] != '\n' && parse[i])
	// {
	// 	pname[r][j] = parse[i];
	// 	j++;
	// }
	return (i);
}

static int		lem_fill_rooms(t_lemsize *size, t_array *parse, void *name, \
								void *links)
{
	int			ants_rooms_links;
	int			i;
	int			ants;

	i = -1;
	ants_rooms_links = 0;
	while (LEM[++i])
		if (LEM[i] == '#')
			while (LEM[i] && LEM[i] != '\n')
				i++;
		else if (ft_isalnum(LEM[i]))
		{
			if ((ants_rooms_links ? 0 : ++ants_rooms_links) && \
				(ants = ft_atoi(LEM + i)))
				while (ft_isdigit(LEM[i]) && LEM[i] != '\n')
					i++;
			else if (++ants_rooms_links <= size->rooms)
				i += lem_fill_name(size, LEM + i, name, ants_rooms_links - 1);
			else
				i += lem_fill_links(size, LEM + i, links, name);
		}
	return (ants);
}

void			lem_parser(t_array *parse, t_lemsize *size)
{
	t_rooms		rooms[size->rooms];//[name][lnks1, 3, 4, 5]->[][]->[][]...
	char		name[size->rooms][size->maxname];
	int			links[size->rooms][size->maxlinks];
	int			ants;

	ft_bzero(&rooms, sizeof(rooms));
	ft_bzero(&name, sizeof(name));
	ft_bzero(&links, sizeof(links));
	ants = lem_fill_rooms(size, parse, name, links);

	rooms[0].roomname = "toto";
	rooms[1].roomname = "tata";
	ft_printf("%s\n", LEM);
	ft_printf("ants %d\n", ants);
	for (int i = 0; i < size->rooms; i++) {
		ft_printf("[%s] links : ", rooms[i].roomname);
		for (int k = 0; k < size->maxlinks; k++) {
			ft_printf("[%d]", rooms[i].links[k]);}
		ft_printf("\n");}
}
