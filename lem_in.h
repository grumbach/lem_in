/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 09:31:15 by agrumbac          #+#    #+#             */
/*   Updated: 2017/03/11 16:03:31 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# define LEM ((char*)(parse->content))
# define BUF_SIZE 32

typedef struct		s_lemsize
{
	int				rooms;
	int				maxname;
	int				maxlinks;
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
void				lem_parser(t_array *parse, t_lemsize *size);

#endif
