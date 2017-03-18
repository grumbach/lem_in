/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 09:30:27 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/18 21:47:55 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		errors(const int err, const char *name)
{
	ft_putstr_fd("lem-in: ", 2);
	if (err == 2)
		ft_putstr_fd("illegal option -- ", 2);
	if (name)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(" ", 2);
	}
	if (err == 0)
		ft_putendl_fd(strerror(errno), 2);
	else if (err == 1)
		ft_putstr_fd("ERROR\n", 2);
	else if (err == 2)
		ft_putstr_fd("\nusage : lem_in [-g] < [file]\n", 2);
	else if (err == 3)
		ft_putstr_fd("\n", 2);
	else if (err == 4)
		ft_putstr_fd("Jackass detected...\n", 2);
	exit(1);
}

static void	parse_em(t_array *parse, t_lemsize *size)
{
	char		*line;
	int			ret;
	int			ant_room_lnk;

	ant_room_lnk = 1;
	line = NULL;
	while ((ret = ft_get_next_line(0, &line)) && ret != -1)
	{
		if (!lem_check(line, size, &ant_room_lnk))
			break ;
		ret = ft_strlen(line);
		line[ret] = '\n';
		ft_arrayappend(parse, line, ret + 1);
		ft_memdel((void**)(&line));
	}
	if (ret == -1 || ft_strlen(LEM) > 10000)
	{
		ft_arraydel(&parse);
		if (ret == -1)
			errors(0, 0);
		errors(4, 0);
	}
}

int			main(int ac, char **av)
{
	t_array		*parse;
	t_lemsize	size;

	ft_bzero(&size, sizeof(t_lemsize));
	if (ac > 1)
	{
		if (!ft_strcmp(av[1], "-g"))
			size.gflag = 1;
		else
			errors(2, av[1]);
	}
	if (!(parse = ft_arraynew(1)))
		errors(0, 0);
	parse_em(parse, &size);
	lem_set_colony(parse, &size);
	if (size.gflag)
		ft_printf("%d %d %d %d %d %d %d\n", size.rooms, size.maxname, \
		size.maxlinks, size.min.x, size.max.x, size.min.y, size.max.y);
	ft_printf("%s", LEM);
	ft_arraydel(&parse);
	return (0);
}
