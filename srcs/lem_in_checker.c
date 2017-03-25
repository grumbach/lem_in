/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 00:48:40 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/15 12:37:56 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	lnk_check(const char *line, t_lemsize *size)
{
	size->maxlinks++;
	if (*line == 'L' || !*line)
		return (0);
	while (*line && *line != '-' && *line != ' ')
		line++;
	if (*line != '-')
		return (0);
	line++;
	if (*line == 'L' || *line == '#' || !*line)
		return (0);
	while (*line && *line != '-' && *line != ' ')
		line++;
	return (!*line);
}

static void	coords_get(const char *line, t_lemsize *size)
{
	t_xy	read;

	read.x = ft_atoi(line);
	read.y = ft_atoi(line + ft_intlen(read.x) + 1);
	if (!size->rooms)
	{
		size->max.x = read.x;
		size->min.x = read.x;
		size->max.y = read.y;
		size->min.y = read.y;
	}
	else
	{
		size->max.x = MAX(size->max.x, read.x);
		size->min.x = MIN(size->min.x, read.x);
		size->max.y = MAX(size->max.y, read.y);
		size->min.y = MIN(size->min.y, read.y);
	}
}

static int	coords_check(const char *line, t_lemsize *size)
{
	int		i;

	i = 0;
	if (line[i] == '-')
		i++;
	if (!line[i] || !ft_isdigit(line[i]))
		return (0);
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != ' ')
		return (0);
	i++;
	if (line[i] == '-')
		i++;
	if (!line[i] || !ft_isdigit(line[i]))
		return (0);
	while (ft_isdigit(line[i]))
		i++;
	if (line[i])
		return (0);
	coords_get(line, size);
	size->rooms++;
	return (1);
}

static int	room_check(const char *line, t_lemsize *size, \
					int *ant_room_lnk)
{
	int		i;

	i = 0;
	if (line[0] == 'L' || line[0] == '#' || !line[0])
		return (0);
	while (line[i] && line[i] != ' ' && line[i] != '-')
		i++;
	if (line[i] == '-')
	{
		*ant_room_lnk = 3;
		return (lnk_check(line, size));
	}
	if (line[i] != ' ')
		return (0);
	size->maxname = MAX(size->maxname, i);
	i++;
	return (coords_check(line + i, size));
}

int			lem_check(const char *line, t_lemsize *size, \
					int *ant_room_lnk)
{
	if (line[0] == '#')
		return (1);
	else if (*ant_room_lnk == 1)
	{
		*ant_room_lnk = 2;
		size->ants = ft_atoi(line);
		if (line[0] == '-')
			line++;
		while (ft_isdigit(*line))
			line++;
		return (!*line);
	}
	else if (*ant_room_lnk == 2)
		return (room_check(line, size, ant_room_lnk));
	else if (*ant_room_lnk == 3)
		return (lnk_check(line, size));
	return (1);
}
