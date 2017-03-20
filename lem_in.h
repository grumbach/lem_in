/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 09:31:15 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/20 03:54:14 by agrumbac         ###   ########.fr       */
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
# define LERROR(i, c) {ft_arraydel(&parse); errors(i, c);}

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
	int				type;
	int				ants;
}					t_rooms;

void				errors(const int err, const char *name);
int					lem_check(const char *line, t_lemsize *size, \
					int *ant_room_lnk);
void				lem_set_colony(t_array *parse, const t_lemsize *size);
int					lem_initialize_em(void *links, char **par, \
					const t_lemsize *size);
char				*lem_check_link(char *par);
int					lem_find_name(char *big, void *names, int len, \
					const t_lemsize *size);
void				lem_smart_ant(void *rooms, const t_lemsize *size);

#endif
