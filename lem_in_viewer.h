#ifndef LEM_IN__VIEWER.H
# define LEM_IN_VIEWER.H

# define WIDTH 		1024
# define HEIGHT		632

# define K_A		0
# define K_LEFT		123
# define K_D		2
# define K_RIGHT	124
# define K_S		
# define K_DOWN		125
# define K_W		13
# define K_UP		126

# define LEFT		1
# define RIGHT		2
# define DOWN		4
# define UP			8

# define ROOMS		room[ants->max.y][ants->max.x]
# define LINKS		room[ants->max.y][ants->max.x]->links[ants->max.y][ants->max.x]
# define NAME		rooms[i.y][i.x]->name
# define TYPE		rooms[i.y][i.x]->type

# include "libft.h"//

typedef struct	s_xy
{
	int			x;
	int			y;
}				t_xy;

/*
** struct for mlx
*/

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			endian;
	int			sl;
	t_xy		i;
}				t_mlx;

/*
** *name is room's name
** type is 1 if starting, 2 if middle and 3 if ending
** links are to other rooms are stored inside links
*/

typedef struct	s_rooms
{
	char		*name;
	int			type;
	int			links[ants->max.y][ants->max.x]
}				t_rooms;

/*
** mlx is for data relative to the mlx,
** nb is the nb of ants
** room_nb is the number of rooms used for our full stack array
** room_index -> may be usefull in the future//
** max is the size of the map to be drawn and room location
*/

typedef struct	s_ants
{
	t_mlx		mlx;
	int			nb;
	int			room_nb;
	int			room_index;
	t_xy		max;
	int			loop;
	char		*tmp_s1;
	char		*tmp_s2;
}				t_ants;

/*
** Initialize stack functions
*/

void	init_rooms(t_ants *ants, *ROOMS);
void	init_links(t_ants *ants, t_xy pos, *ROOMS, *LINKS);

/*
** parsing functions
*/

void	lem_in_parsing(void);
int		not_comment(char *line, int *start);
void	add_room(t_ants *ants, char *s, t_room room, int type);
int		check_room_format(t_ants ants, char *s, t_index room[ants->room_nb]);
void 	parse_links(t_ants *ants, char *s);

/*
** misc
*/

void	lem_in_error(char *s, int *loop);

#endif
