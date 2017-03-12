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

# define ANTS		t_ants	*ants;
# define ROOMS		t_rooms room[ants->max.y][ants->max.x]
# define LINKS		int		room[ants->max.y][ants->max.x]->links[ants->max.y][ants->max.x]
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
	t_xy		cell_dim;
}				t_ants;

/*
** Rooms and their links initialization 
*/

void	init_rooms(t_ants *ants, *ROOMS);
void	init_links(t_ants *ants, t_xy pos, *ROOMS, *LINKS);

/*
** GLOBAL PARSING
*/

void	lem_in_parsing(void);
int		not_comment(char *line, int *start);

/*
** parsing new rooms
*/

void	add_room(t_ants *ants, char *s, t_room room, int type);
int		check_room_format(t_ants ants, char *s, t_index room[ants->room_nb]);

/*
** parsing link between rooms
*/

void 	parse_links(t_ants *ants, char *s);
int 	check_room_name_and_link(ANTS, ROOMS, LINKS);
int 	link_to_other_room(t_xy pos, ANTS, ROOMS, LINKS);

/*
** misc
*/

void	lem_in_error(char *s, int *loop);

/*
** mlx functions
*/

void	hook_exposure(t_ants *ants);
int		hook(int k, t_ants *ants);
int		hook_move(int k, t_ants *e);

/*
** drawing functions
*/

int		draw_ants(t_ants *ants);
void	draw_rooms(ANTS, ROOMS)
void	draw_room(t_xy pos, ANTS, ROOMS);
void	ft_put_pixel(t_mlx *m, int x, int y, int color);



#endif
