/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_worker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 22:02:04 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/31 10:41:58 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	lem_get_end(char *par, void *rooms, void *names, \
			const t_lemsize *size)
{
	int			i;
	char		*see;
	char		tmpname[size->maxname + 1];

	t_rooms(*room)[size->rooms + 1];
	room = rooms;
	see = NULL;
	i = 0;
	ft_bzero(tmpname, sizeof(tmpname));
	if (!(see = ft_strstr(par, "\n##end\n")))
		return (-1);
	see = see + 7;
	while (see[i] != ' ' && see[i] != '\n' && see[i] && i < size->maxname)
	{
		tmpname[i] = see[i];
		i++;
	}
	if (see[i] != ' ' || !see[i])
		return (-1);
	(*room)[lem_find_name(tmpname, names, i, size)].type += END;
	return (1);
}

int			lem_start_end(char *par, void *rooms, void *names, \
			const t_lemsize *size)
{
	int			i;
	char		*see;
	char		tmpname[size->maxname + 1];

	t_rooms(*room)[size->rooms + 1];
	room = rooms;
	see = NULL;
	i = 0;
	ft_bzero(tmpname, sizeof(tmpname));
	if (!(see = ft_strstr(par, "\n##start\n")))
		return (0);
	see = see + 9;
	while (see[i] != ' ' && see[i] != '\n' && see[i] && i < size->maxname)
	{
		tmpname[i] = see[i];
		i++;
	}
	if (see[i] != ' ' || !see[i])
		return (0);
	(*room)[lem_find_name(tmpname, names, i, size)].type += START;
	return (lem_get_end(par, rooms, names, size));
}

char		*lem_check_link(char *par)
{
	char		*see;

	if ((see = ft_strchr(par, '-')))
		while (*(see - 1) == ' ')
		{
			par = see + 1;
			if (!(see = ft_strchr(par, '-')))
				break ;
		}
	return (see);
}

int			lem_initialize_em(void *links, char **par, const t_lemsize *size)
{
	int			(*link)[size->rooms + 1][size->maxlinks + 1];
	int			i;
	int			j;

	link = links;
	i = -1;
	if (size->ants <= 0)
		return (0);
	while (++i < size->rooms + 1)
	{
		j = -1;
		while (++j < size->maxlinks + 1)
			(*link)[i][j] = -1;
	}
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

int			lem_find_name(char *par, void *names, int len, \
				const t_lemsize *size)
{
	char		(*name)[size->rooms + 1][size->maxname + 1];
	int			i;

	name = names;
	i = -1;
	while (++i < size->rooms)
		if (ft_strnstr(par, (*name)[i], len))
			return (i);
	return (-1);
}
