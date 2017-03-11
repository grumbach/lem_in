/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 09:30:27 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/11 18:41:16 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

long		errors(const int err, const char *name)
{
	ft_putstr_fd("lem-in: ", 2);
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
		ft_putstr_fd("Invalid format\n", 2);
	else if (err == 4)
		ft_putstr_fd("Jackass detected...\n", 2);
	exit(1);
	return (0);
}

static void	lem_links(t_array *parse, t_lemsize *size, int *i)
{
	LEM[*i] == '-' ? (*i)++ : errors(2, 0);
	if (!(ft_isalnum(LEM[*i]) && LEM[*i] != '\n' && LEM[*i]))
		errors(2, 0);
	while (ft_isalnum(LEM[*i]) && LEM[*i] != '\n' && LEM[*i])
		(*i)++;
	size->maxlinks += 1;
}

static void	lem_rooms_links(t_array *parse, int *ants_rooms_links, \
							t_lemsize *size, int *i)
{
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
		lem_links(parse, size, i);
}

static void	lem_reader(t_array *parse, t_lemsize *size)
{
	int			i;
	int			ants_rooms_links;

	ants_rooms_links = 0;
	i = 0;
	while (LEM[i])
	{
		if (LEM[i] == '\n')
			errors(2, 0);
		if (LEM[i] == '#')
			while (LEM[i] && LEM[i] != '\n')
				i++;
		else if (ft_isalnum(LEM[i]))
		{
			if (ants_rooms_links ? 0 : ++ants_rooms_links)
				while (ft_isdigit(LEM[i]) && LEM[i] != '\n')
					i++;
			else if (LEM[i] != 'L')
				lem_rooms_links(parse, &ants_rooms_links, size, &i);
		}
		if (LEM[i] != '\n' && LEM[i])
			errors(2, 0);
		i++;
	}
}

int			main(void)
{
	t_array		*parse;
	t_lemsize	size;
	int			ret;
	char		buf[BUF_SIZE + 1];

	ft_bzero(&size, sizeof(t_lemsize));
	ft_bzero(buf, BUF_SIZE + 1);
	if (!(parse = ft_arraynew(1)))
		errors(0, 0);
	while ((ret = read(0, buf, BUF_SIZE)) && ret != -1)
	{
		buf[ret] = 0;
		ft_arrayappend(parse, buf, ret);
	}
	if (ret == -1)
	{
		ft_arraydel(&parse);
		errors(0, 0);
	}
	if (ft_strlen(parse.content) > 10000)
		exit(4, 0);
	lem_reader(parse, &size);
	lem_parser(parse, &size);
	ft_arraydel(&parse);
	return (0);
}
