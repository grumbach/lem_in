/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_worker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 22:02:04 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/18 22:58:52 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	lem_reset_links(void *links, const t_lemsize *size)
{
	int			(*link)[SIZEROOM][SIZELINK];
	int			i;
	int			j;

	link = links;
	i = -1;
	while (++i < SIZEROOM)
	{
		j = -1;
		while (++j < SIZELINK)
		{
			(*link)[i][j] = -1;
		}
	}
}

int		lem_find_name(char *par, void *names, int len, const t_lemsize *size)
{
	char		(*name)[SIZEROOM][SIZENAME];
	int			i;

	// ft_printf(">%.*s(%d)<", len, par, len);
	name = names;
	i = -1;
	while (++i < SIZEROOM)
	{
		// ft_printf("name[%d]{%s} == {%.*s}\n", i, &(name[i][0]), len, par);
		if (ft_strnstr(par, (char*)&(name[i][0]), len))
			return (1);
	}
	return (0);
}
