/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 09:31:15 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/15 10:05:25 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# define MAX(a, b) (a > b ? a : b)
# define MIN(a, b) (a < b ? a : b)
# define LEM ((char*)(parse->content))

typedef struct		s_xy
{
	int				x;
	int				y;
}					t_xy;

typedef struct		s_lemsize
{
	int				ants;
	int				rooms;
	int				maxname;
	int				maxlinks;
	t_xy			max;
	t_xy			min;
	int				gflag;
}					t_lemsize;

typedef struct		s_rooms
{
	char			*roomname;
	int				*links;
}					t_rooms;

typedef struct		s_lem
{
	t_array			*parse;
	t_rooms			*rooms;
}					t_lem;

long				errors(const int err, const char *name);
void				lem_set_colony(const t_array *parse, const t_lemsize *size);
int					lem_check(const char *line, t_lemsize *size, \
					int *ant_room_lnk);

#endif
